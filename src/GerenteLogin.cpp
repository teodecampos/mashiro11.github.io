#include "GerenteLogin.h"

//#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
	#define DEBUG_PRINT(x)  
#endif

GerenteLogin::GerenteLogin()
{
}


GerenteLogin::~GerenteLogin()
{
}

string GerenteLogin::_digiteSenha(){
    cout << "_Digite sua senha: " << endl;
    string s;
    #ifdef __linux__
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        do{
            getline(cin, s);
        }while(s == "");
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #else
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
        DWORD mode = 0;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
        do{
            getline(cin, s);
        }while(s == "");
        SetConsoleMode(hStdin, mode);
    #endif
    return s;
}

Usuario GerenteLogin::NovoUsuario(string matricula) {
	Usuario usuario;
	string nome;
	string senha;
	cout << "Nome: ";
	cin >> nome;
	cout << "Senha: ";
	cin >> senha;
	usuario.SetMatricula(matricula);
	usuario.SetNome(nome);
	usuario.SetSenha(senha);
	GerenteBD::InsereUsuario(usuario);
    _CriaBancoDeFotos(matricula);
	return usuario;
}


Usuario GerenteLogin::Credencia(string matricula) {
	DEBUG_PRINT("GerenteLogin::Credencia - inicio");
	Usuario usuario;
    usuario.SetNome("fake");
    usuario.SetSenha("");
	if ( GerenteBD::ExisteUsuario(matricula) ) { //usuario cadastrado
		DEBUG_PRINT("	Usuario cadastrado na base de dados");
		if (_ReconheceFace(matricula)) {//reconhece o rosto
			//reconheceu pelo rosto
			//modifica a instância de usuario
			usuario = GerenteBD::BuscaUsuario(matricula);
			DEBUG_PRINT("		Matricula: " << usuario.GetMatricula());
			DEBUG_PRINT("		Nome: " << usuario.GetNome());
			return usuario;
		}
		else {//caso nao reconhecido
			string senha;
			cout << "Usuario nao reconhecido" << endl;
			senha = _digiteSenha();
			if (GerenteBD::ChecaUsuario(matricula, senha)) {
				usuario = GerenteBD::BuscaUsuario(matricula);
				_AtualizaBancoDeFotos();
				DEBUG_PRINT("		Matricula: " << usuario.GetMatricula());
				DEBUG_PRINT("		Nome: " << usuario.GetNome());
			}
			return usuario;
		}
	}
	DEBUG_PRINT("GerenteLogin::Credencia - fim");
	return usuario;
}

bool GerenteLogin::_ReconheceFace(string matricula) {
	cout << " INICO RECONHECE\n";
    String face_cascade_name = "resources/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "resources/haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    String window_name = "Reconhece face";
    VideoCapture capture;
    int prediction;
    
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ cout << "--(!)Error loading face cascade\n"; mySleep(3000); return false; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ cout << "--(!)Error loading eyes cascade\n"; mySleep(3000); return false; };
    //-- 2. Read the video stream
    capture.open( "http://192.168.1.123:4747/mjpegfeed?640x480" );
    if ( ! capture.isOpened() ) { 
        cout << "--(!)Error opening video capture\n"; 
        mySleep(3000); return false; 
    }

    //$$$$$$$$$$$ cria csv
    system("python resources/cria_csv.py resources/fotos/");
    // Get the path to your CSV.
    string path_fotos_csv = "resources/fotos.csv";
    cout << "csv criado\n";
    // These vectors hold the images and corresponding labels.
    vector<Mat> images;
    vector<int> labels;
    // Read in the data. This can fail if no valid
    // input filename is given.
    try {
        _read_csv(path_fotos_csv, images, labels);
    } catch (cv::Exception& e) {
        std::cerr << "Error opening file \"" << path_fotos_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        mySleep(3000);
        return false;
    }
    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(Error::StsError, error_message);
    }
    int im_width = images[0].cols;
    int im_height = images[0].rows;
    // $$$$$$$ TREINAR FACES
    Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
    model->train(images, labels);

    Mat frame;

    //$$ loop 

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            mySleep(3000);
            break;
        }
        //-- 3. Apply the classifier to the frame

        //$$$$$$$$$$$$$$$$$$$$$$$$$$ reconhece( frame, model ); $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        std::vector<Rect> faces;
        Mat frame_gray;
        Mat original = frame.clone();
        cvtColor( original, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
        //-- Detect faces
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
        for ( size_t i = 0; i < faces.size(); i++ )
        {
            Rect face_i = faces[i];
            // Crop the face from the image. So simple with OpenCV C++:
            Mat face = frame_gray(face_i);
        
            Mat face_resized;
            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

            //eyes
            Mat faceROI = frame_gray( faces[i] );
            std::vector<Rect> eyes;
            eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
            if (eyes.size() > 0 ){
                // Now perform the prediction, see how easy that is:
                prediction = model->predict(face_resized);
                // And finally write all we've found out to the original image!
                // First of all draw a green rectangle around the detected face:
                rectangle(original, face_i, CV_RGB(0, 255,0), 1);
                // Create the text we will annotate the box with:
                string box_text = format("Prediction = %d", prediction);
                // Calculate the position for annotated text (make sure we don't
                // put illegal values in there):
                int pos_x = std::max(face_i.tl().x - 10, 0);
                int pos_y = std::max(face_i.tl().y - 10, 0);
                // And now put it into the image:
                putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
            }
        }
        //-- Show what you got
        imshow( window_name, original );
        char c = (char)waitKey(10);
        if( c == 27 ) {
            destroyAllWindows();
            break; 
        } // escape
    }
	
	if (prediction == atoi( matricula.c_str() )) {//caso reconheça pelo rosto
		cout << "Usuario reconhecido. "<< endl;
		mySleep(3000);
		return true;
	}
	else {//caso contrario
		cout << "Rosto nao reconhecido" << endl;
		mySleep(3000);
		return false;
	}

}

void GerenteLogin::_AtualizaBancoDeFotos(){

}

bool GerenteLogin::_CriaBancoDeFotos(string matricula) {
    cout << "CRIA PASTA FOTOS\n";
	String face_cascade_name =  "resources/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name =  "resources/haarcascade_eye_tree_eyeglasses.xml";
    String path_fotos = "resources/fotos/";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    String window_name = "Capture - Face detection";
    

    std::vector<Rect> faces;
   
    VideoCapture capture;
    Mat frame;
    Mat frame_gray;
                //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ cout << "--(!)Error loading face cascade: " << face_cascade_name << endl; mySleep(3000); return false; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ cout << "--(!)Error loading eyes cascade: " << eyes_cascade_name << endl; mySleep(3000); return false; };
    //-- 2. Read the video stream
    capture.open( "http://192.168.1.123:4747/mjpegfeed?640x480" );
    // evita criar pasta vazia
    if ( ! capture.isOpened() ) { 
        cout << "--(!)Error opening video capture\n"; 
        mySleep(3000);
        return false;
        
    }
    
    String pasta = path_fotos + matricula;
    //cout << pasta << endl;

    #ifdef __linux__ 
        const char * c = pasta.c_str();

        char * writable = new char[pasta.size() + 1];
        std::copy(pasta.begin(), pasta.end(), writable);
        writable[pasta.size()] = '\0';

        int resp = mkdir( writable, 0777 );
        if (resp == 0 ){
            std::cout << "Pasta criada, com sucesso\n";
        } else if (resp == -1) {
            std::cout << "A pasta ja existe. FIM!\n";
            mySleep(3000);
            return false;
        } else {
            std::cout << "Erro desconhecido.\n";
            mySleep(3000);
            return false;
        }
    #else // windows
        int resp = mkdir( pasta );
        if (resp == 0 ){
            std::cout << "Pasta criada, com sucesso\n";
        } else if (resp == -1) {
            std::cout << "A pasta ja existe. FIM!\n";
            mySleep(3000);
            return false;
        } else {
            std::cout << "Erro desconhecido.\n";
            mySleep(3000);
            return false;
        }
    #endif

    int contador_fotos = 0;
    time_t now, later;
    int iniciar_contagem = 0;

    while ( capture.read(frame) )
    {
        //cout << "entra no loop\niniciar_contagem: " << iniciar_contagem << "\ncontador_fotos: " << contador_fotos << endl;
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            mySleep(3000);
            return false;
        }
        cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$444
        //-- Detect faces
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
        for ( size_t i = 0; i < faces.size(); i++ )
        {
            //Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            //ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 150, 0, 255 ), 4, 8, 0 );
            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);
            rectangle(frame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
            Mat faceROI = frame_gray( faces[i] );
            std::vector<Rect> eyes;
            //-- In each face, detect eyes
            eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
            for ( size_t j = 0; j < eyes.size(); j++ )
            {
                Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
                int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
            }
            if (eyes.size() > 0 && contador_fotos < 10)
            {
                if ( iniciar_contagem == 0){
                    time(&now);/* get current time; same as: now = time(NULL)  */
                    iniciar_contagem = 1;
                    //cout << "iniciar_contagem 0" << endl;
                } else if (iniciar_contagem == 1 ){
                    time(&later);
                    double seconds = difftime(later, now);
                    //cout << seconds << " segundos\n";
                    if (seconds > 1 ){ /* Espera 1 seg*/
                        std::stringstream ss;
                        ss << pasta << "/" << contador_fotos << "-foto.png";
                        Mat myface = faceROI.clone();
                        imwrite(ss.str(), myface);
                        iniciar_contagem = 0;
                        contador_fotos += 1;
                        cout << "Foto: " << ss.str() << endl; 
                        if (contador_fotos == 10){
                        	destroyAllWindows();
                        	mySleep(3000);
                            cout << "Capturei 10 fotos. FIM.\n";
                            return true;
                        }
                    }
                }
            }
        }
        imshow( window_name, frame );
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    }
}

void GerenteLogin::_read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator) 
{
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(Error::StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#else
    Sleep(sleepMs);
#endif
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
