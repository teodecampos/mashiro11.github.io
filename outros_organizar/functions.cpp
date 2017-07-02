void criaObj(signed long long int numero, string nome, string sobrenome){
	Lista usuario;
	char disciplina[40] = {0};
	string titulo = to_string(numero);

	char *ex = &titulo[0u];

	usuario.numero = numero;
	usuario.nome = nome.c_str();
	usuario.sobrenome = sobrenome.c_str();

	FILE *Arquivo;

	char diretorio[50];
	strcpy (diretorio,"C:\\Users\\Felipe\\Desktop\\");
	strcat (diretorio,ex);
	strcat (diretorio,".txt");

	int respo, pass = 0;
	while (1)
	{
		cout << "Deseja adicionar Disciplina? 1 - Sim ";
		cin >> respo;
		if (respo == 1)
		{
		    cout << "\nDigite a Disciplina: ";
			if (pass == 0)
			{
				cin.getline(disciplina, sizeof(disciplina));
				cin.getline(disciplina, sizeof(disciplina));
		        usuario.disciplina = disciplina;
		        cout << endl;
		        pass = 1;
			} else {
				char di[40] = {0};
				strcat (disciplina,", ");
				cin.getline(di, sizeof(di));
				cin.getline(di, sizeof(di));
				strcat (disciplina, di);
		        usuario.disciplina = disciplina;
		        cout << endl;
			}
		} else {
			if (pass == 0)
			{
				strcpy (disciplina," ");
			}
			break;
		}
	}

	Arquivo = fopen(strcat(ex,".txt"),"w");
	fputs (nome.c_str(), Arquivo);
	fputs ("\n", Arquivo);
	fputs (sobrenome.c_str(), Arquivo);
	fputs ("\n", Arquivo);
	fputs (diretorio, Arquivo);
	fputs ("\n", Arquivo);
	fputs (disciplina, Arquivo);
	fclose(Arquivo);

	cout << "\nCadastrado com sucesso!";
	sleep(1);
}

int existencia(signed long long int numero){
	FILE *Arquivo;

	string titulo = to_string(numero);

	char* ex = &titulo[0u];

	Arquivo = fopen(strcat(ex,".txt"),"r");
	if(Arquivo){
		fclose(Arquivo);
		return 1;
	}
	fclose(Arquivo);
	return 0;
}

void insere(){
    signed long long int numero;
    char nome[20];
    char sobrenome[40];
    char disciplina[40];

    cout << "\nDigite o Numero: ";
    cin >> numero;
    cout << endl;

    if(!existencia(numero)){
        cout << "Digite o Nome: ";
        cin.getline(nome, sizeof(nome));
		cin.getline(nome, sizeof(nome));
        cout << endl;

        cout << "Digite o Sobrenome: ";
        cin.getline(sobrenome, sizeof(sobrenome));
        cout << endl;

        criaObj(numero, nome, sobrenome);
    } else {
    	cout << "\nUsuario ja existe!";
		sleep(1);
    }
}

void edita(){
    signed long long int numero;
    char buff[100] = {0};
    char nome[20];
    char sobrenome[40];
    char diretorio[50];
    char disciplina[40];

	FILE *Arquivo;

	system("cls");

    cout << "\nDigite o Numero: ";
    cin >> numero;
    cout << endl;

    if (existencia(numero))
    {
		string titulo = to_string(numero);
		string resp;

		char* ex = &titulo[0u];

		Arquivo = fopen(strcat(ex,".txt"),"r+");

		cout << "\nUsuario encontrado!\n";
        cout << "------------------------\n";
        cout << "Nome: ";
		char *dado = {0};
		dado = fgets (buff, 100, Arquivo);
		strcpy(nome, dado);
		cout << dado;
        cout << "Sobrenome: ";
		dado = fgets (buff, 100, Arquivo);
		strcpy(sobrenome, dado);
		cout << dado;
        cout << "Diretorio: ";
		dado = fgets (buff, 100, Arquivo);
		strcpy(diretorio, dado);
		cout << dado;
        cout << "Disciplina: ";
		dado = fgets (buff, 100, Arquivo);
		strcpy(disciplina, dado);
		cout << dado;
        cout << "\n------------------------\n";

        fclose(Arquivo);
		cout << "\nDeseja editar:\n\n";
        cout << "1 - Numero\n";
        cout << "2 - Nome\n";
        cout << "3 - Sobrenome\n";
        cout << "4 - Disciplina\n\n";
		cin >> resp;

		if (resp == "1")
		{
			int result;
			string oldnbr;

			cout << "\nNovo numero: ";

			if (cin >> result)
			{
				oldnbr = to_string(numero);
				string titulo = to_string(result);

				char* exe = &oldnbr[0u];
				char* exem = &titulo[0u];

				rename(strcat(exe,".txt"), strcat(exem,".txt"));

				Arquivo = fopen(exem,"w");

				fputs (nome, Arquivo);
				fputs (sobrenome, Arquivo);

				strcpy (diretorio,"C:\\Users\\Felipe\\Desktop\\");
				strcat (diretorio,exem);

				fputs (diretorio, Arquivo);
				fputs ("\n", Arquivo);
				string tmp = disciplina;
				fputs (tmp.c_str(), Arquivo);

				fclose(Arquivo);

				cout << "\nAlterado com sucesso!\n";
				sleep(1);
			} else {
				cout << "\nDigite apenas numeros!\n";
				cin.clear();
				sleep(1);
			}
		} else if (resp == "2")
		{
			Arquivo = fopen(ex,"w");

			char nomeinput[20];
			cout << "\nNovo nome: ";
			cin.getline(nomeinput, sizeof(nomeinput));
			cin.getline(nomeinput, sizeof(nomeinput));
			fputs (nomeinput, Arquivo);
			fputs ("\n", Arquivo);
			fputs (sobrenome, Arquivo);

			strcpy (diretorio,"C:\\Users\\Felipe\\Desktop\\");
			strcat (diretorio,ex);

			fputs (diretorio, Arquivo);
			fputs ("\n", Arquivo);
			string tmpo = disciplina;
			fputs (tmpo.c_str(), Arquivo);

			fclose(Arquivo);

			cout << "\nAlterado com sucesso!\n";
			sleep(1);
		} else if (resp == "3")
		{
			Arquivo = fopen(ex,"w");

			char sobrenomeinput[40];
			cout << "\nNovo sobrenome: ";
			cin.getline(sobrenomeinput, sizeof(sobrenomeinput));
			cin.getline(sobrenomeinput, sizeof(sobrenomeinput));
			fputs (nome, Arquivo);
			string tmp = sobrenomeinput;
			fputs (tmp.c_str(), Arquivo);
			fputs ("\n", Arquivo);

			strcpy (diretorio,"C:\\Users\\Felipe\\Desktop\\");
			strcat (diretorio,ex);

			fputs (diretorio, Arquivo);
			fputs ("\n", Arquivo);
			string tmpo = disciplina;
			fputs (tmpo.c_str(), Arquivo);

			fclose(Arquivo);

			cout << "\nAlterado com sucesso!\n";
			sleep(1);
		} else if (resp == "4")
		{
			Arquivo = fopen(ex,"w");

			char disciplina[40];

			int respo = 1, pass = 0;
			while (1)
			{
				if (respo == 1)
				{
				    cout << "\nNova disciplina: ";
					if (pass == 0)
					{
						cin.getline(disciplina, sizeof(disciplina));
						cin.getline(disciplina, sizeof(disciplina));
				        cout << endl;
				        pass = 1;
					} else {
						char di[40] = {0};
						strcat (disciplina,", ");
						cin.getline(di, sizeof(di));
						cin.getline(di, sizeof(di));
						strcat (disciplina, di);
				        cout << endl;
					}
				} else {
					if (pass == 0)
					{
						strcpy (disciplina," ");
					}
					break;
				}
				cout << "Deseja adicionar mais Disciplinas? 1 - Sim ";
				cin >> respo;
			}

			fputs (nome, Arquivo);
			fputs (sobrenome, Arquivo);

			char diretorio[50];
			strcpy (diretorio,"C:\\Users\\Felipe\\Desktop\\");
			strcat (diretorio,ex);
			strcat (diretorio,".txt");

			fputs (diretorio, Arquivo);
			fputs ("\n", Arquivo);
			string tmp = disciplina;
			fputs (tmp.c_str(), Arquivo);

			fclose(Arquivo);

			cout << "\nAlterado com sucesso!\n";
			sleep(1);
		} else {
			cout << "\nDigite uma resposta valida!";
			sleep(1);
		}
    } else {
		cout << "\nUsuario nao existe!";
		sleep(1);
    }

}

void busca(){
    signed long long int numero;
	char buff[100] = {0};
	long lSize;

	FILE *Arquivo;

    cout << "\nDigite o Numero: ";

	if (cin >> numero)
	{
	    if (existencia(numero))
	    {
			string titulo = to_string(numero);

			char* ex = &titulo[0u];

			Arquivo = fopen(strcat(ex,".txt"),"r");

			cout << "\nUsuario encontrado!\n";
	        cout << "------------------------\n";
	        cout << "Nome: ";
			char *name = {0};
			name = fgets (buff, 100, Arquivo);
			cout << name;
	        cout << "Sobrenome: ";
			char *sname = {0};
			sname = fgets (buff, 100, Arquivo);
			cout << sname;
	        cout << "Diretorio: ";
			char *dire = {0};
			dire = fgets (buff, 100, Arquivo);
			cout << dire;
	        cout << "Disciplina: ";
			char *disc = {0};
			disc = fgets (buff, 100, Arquivo);
			cout << disc;
	        cout << "\n------------------------\n";

			fclose(Arquivo);

			char temp;

			cout << "\nSair? ";
			cin >> temp;
	    } else {
			cout << "\nUsuario nao existe!";
			sleep(1);
	    }
	} else {
		cout << "\nDigite apenas numeros!\n";
		cin.clear();
		sleep(1);
	}
}

void deleta(){
    signed long long int numero;

    cout << "\nDigite o Numero: ";
    cin >> numero;
    cout << endl;

	FILE *Arquivo;

	string titulo = to_string(numero);

	char* ex = &titulo[0u];

	Arquivo = fopen(strcat(ex,".txt"),"r+");
	if(Arquivo){
		fclose(Arquivo);
		remove(ex);
		cout << "\nUsuario removido!";
		sleep(1);
	} else {
		fclose(Arquivo);
		cout << "\nUsuario nao existe!";
		sleep(1);
	}
}

void dir(){
	DIR* dir;
	dirent* drnt;
	dir=opendir(".");

	system("cls");
	cout << "\n";
	while(drnt = readdir(dir)){
		cout << drnt->d_name;
		cout << "\n";
	}

	char temp;

	cout << "\nSair? ";
	cin >> temp;
}