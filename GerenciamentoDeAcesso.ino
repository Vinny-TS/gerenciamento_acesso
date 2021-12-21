#include <EEPROM.h>
String usuario;
String senha;
int usuarioLen;
int senhaLen;
int cargoLen;
char cargo;
int sala1;
int sala2;
int led1 = 4;
int led2 = 5;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  while (true)
  //Cria o menu principal
  {
    Serial.println("** MENU - Selecione uma opcao **");
    Serial.println(" ");
    Serial.println("[1] Criar novo usuario");
    Serial.println("[2] Listar usuarios");
    Serial.println("[3] Abrir sala 1");
    Serial.println("[4] Abrir sala 2");
    Serial.println("[5] Listar Eventos");
    Serial.println(" ");
    Serial.println("********************************");
    while (Serial.available() <= 0){}
    int acao = Serial.read();
    switch (acao)
    //Chama as funções de cada opção
    {
    case '1':
      novoUsuario();
      break;
    case '2':
      listaDeUsuarios();
      break;
    case '3':
      abrirPorta1();
      break;
    case '4':
      abrirPorta2();
      break;
    case '5':
      listaEventos();
      break;
    default:
      Serial.println("Opcao invalida, digite um numero de 1 a 5.");
    }
  }
}

void novoUsuario()
//Cria um novo usuário
{
  usuarioLen = 0;
  Serial.println("*[1] Criar novo usuario*");
  Serial.println(" ");
  Serial.println("Digite seu nome");
  while (Serial.available() <= 0){}

  usuario = Serial.readString();
  if (usuario != "")
  {
    EEPROM.put(usuarioLen, usuario);
    Serial.println(usuario);
    senhaLen = usuarioLen + 1;
    Serial.println("Digite sua senha");
    while (Serial.available() <= 0){}
    //Verificação cargo
    senha = Serial.readString();
    if (senha != "")
    {
      EEPROM.put(senhaLen, senha);
      Serial.println(senha);
      Serial.println("Voce e um administrador? Digite 's' ou 'n'");
      while (Serial.available() <= 0){}
      //Define o cargo do usuário
      cargo = Serial.read();
      if (cargo == 's')
      {
        Serial.println("Voce e um administrador");
        Serial.println(" ");
        cargoLen = senhaLen + 1;
        EEPROM.write(cargoLen, cargo);
      }
      else if (cargo == 'n')
      {
        Serial.println("Voce não e um administrador");
        Serial.println(" ");
        cargoLen = senhaLen + 1;
        EEPROM.write(cargoLen, cargo);
      }
    }
  }
}

void listaDeUsuarios()
//Lista os usuários registrados
{
  Serial.println("*[2] Listar usuarios*");
  EEPROM.read(cargo);
  if (cargo == 's')
  {
    Serial.println(usuario);
    Serial.println(" ");
  }
  else
  {
    somenteADM();
  }
}

void abrirPorta1()
//Abertura porta 1
{
  Serial.println("*[3] Abrir sala 1*");
  EEPROM.read(cargo);
  if (cargo == 's')
  {
    Serial.println("Deseja abrir a sala 1? Digite 's' ou 'n'");
    while (Serial.available() <= 0){}

    if (Serial.read() == 's')
    {
      digitalWrite(led1, HIGH);
      Serial.println("Sala 1 aberta");
      delay(5000);
      digitalWrite(led1, LOW);
      sala1 = 1;
      Serial.println("Sala 1 fechada");
      Serial.println(" ");
    }
    else
    {
      Serial.println("Sala fechada");
      Serial.println(" ");
    }
  }
  else
  {
    somenteADM();
  }
}

void abrirPorta2()
//Abertura porta 2
{
  Serial.println("*[4] Abrir sala 2*");
  EEPROM.read(cargo);
  if (cargo == 's')
  {
    Serial.println("Deseja abrir a sala 2? Digite 's' ou 'n'");
    while (Serial.available() <= 0){}

    if (Serial.read() == 's')
    {
      digitalWrite(led2, HIGH);
      Serial.println("Sala 2 aberta");
      delay(5000);
      digitalWrite(led2, LOW);
      sala2 = 1;
      Serial.println("Sala 2 fechada");
      Serial.println(" ");
    }
    else
    {
      Serial.println("Sala fechada");
      Serial.println(" ");
    }
  }
  else
  {
      somenteADM();
  }
}

void listaEventos()
//Lista os eventos de abertura de porta e usuários criados
{
  Serial.println("*[5] Listar Eventos*");
  EEPROM.read(cargo);
  if (cargo == 's')
  {
    Serial.println(usuario);
    Serial.println(senha);
    Serial.println(" ");
    if (sala1 == 1)
    {
      Serial.println("Sala 1 foi aberta");
      Serial.println(" ");
    }
    if (sala2 == 1)
    {
      Serial.println("Sala 2 foi aberta");
      Serial.println(" ");
    }
  }
  else
  {
    somenteADM();
  }
}

void somenteADM(){
    Serial.println("Visivel somente para administradores");
    Serial.println(" ");
}