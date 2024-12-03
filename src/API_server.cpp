// API_server.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "crow.h"

int main() {
    crow::SimpleApp app; // Cria uma aplicação simples do Crow

    // Define uma rota GET na raiz "/"
    CROW_ROUTE(app, "/")([]() {
        return "Olá, Mundo! Este é o servidor Crow funcionando!";
        });

    CROW_ROUTE(app, "/get/dados")([]() {
        crow::json::wvalue data;

        // Estruturando os dados
        data["labels"] = crow::json::wvalue::object();
        data["labels"][0] = "Janeiro";
        data["labels"][1] = "Fevereiro";
        data["labels"][2] = "Março";

        data["values"] = crow::json::wvalue::object();
        data["values"][0] = 40;
        data["values"][1] = 20;
        data["values"][2] = 50;

        // Retornando a resposta JSON com headers CORS
        crow::response res(data);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    CROW_ROUTE(app, "/get/usuariosStatus")([]() {
        crow::json::wvalue data;

        // Criando os arrays de dados como listas JSON válidas
        crow::json::wvalue usuariosAtivos;
        usuariosAtivos["name"] = "Usuários Ativos";
        usuariosAtivos["data"] = crow::json::wvalue::list({ 20, 34, 50, 30, 22, 70, 78, 100, 95, 79, 65, 40 });

        crow::json::wvalue usuariosInativos;
        usuariosInativos["name"] = "Usuários Inativos";
        usuariosInativos["data"] = crow::json::wvalue::list({ 5, 8, 17, 6, 2, 3, 10, 20, 10, 15, 7, 5 });

        // Criando o array principal
        crow::json::wvalue::list usuarios;
        usuarios.push_back(std::move(usuariosAtivos));
        usuarios.push_back(std::move(usuariosInativos));

        // Atribuindo o array ao campo "usuarios"
        data["usuarios"] = std::move(usuarios);

        // Retornando a resposta JSON com headers CORS
        crow::response res(data);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    CROW_ROUTE(app, "/get/usuarios")([]() {
        crow::json::wvalue data;

        // Definindo a lista de usuários
        crow::json::wvalue::list usuarios;

        // Criando alguns exemplos de usuários
        for (int i = 0; i < 5; ++i) { // Adicionando 5 usuários de exemplo
            crow::json::wvalue usuario;
            usuario["id"] = i + 1; // ID único
            usuario["userId"] = "USR" + std::to_string(1000 + i); // Exemplo de userId
            usuario["name"] = "Usuário " + std::to_string(i + 1); // Nome fictício
            usuario["cracha"] = "CR" + std::to_string(200 + i); // Exemplo de crachá
            usuario["isVerified"] = (i % 2 == 0); // Alterna entre true/false
            usuario["avatarUrl"] = "/assets/images/avatar/avatar-" + std::to_string(i + 1) + ".webp"; // Avatar fictício
            usuario["status"] = (i % 4 == 0) ? "banned" : "active"; // Alterna entre "active" e "banned"
            usuario["role"] = std::vector<std::string>{
                "Líder",
                "Engenheiro de Processo",
                "Administrador do sistema",
                "Usuário"
            }[i % 4]; // Alterna entre os cargos listados

            usuarios.push_back(std::move(usuario));
        }

        // Atribuindo a lista de usuários ao objeto JSON principal
        data["usuarios"] = std::move(usuarios);

        // Retornando a resposta JSON com headers CORS
        crow::response res(data);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });




    // Inicia o servidor na porta 8080
    app.port(8080).multithreaded().run();

    return 0;
};


//#include <iostream>

//int main()
//{
//   std::cout << "Hello World!\n";
//}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
