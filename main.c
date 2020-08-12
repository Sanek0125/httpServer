#include <stdio.h>
#include <string.h>

#include "extclib/http.h"

void index_page(int conn, HTTPreq *req); // выгрузка html файла; conn - идентифицируем пользователя; req - запрос клиента
void about_page(int conn, HTTPreq *req);

int main(void) {
	HTTP *serve = new_http("127.0.0.1:7545");

	handle_http(serve, "/", index_page); // обработка
	handle_http(serve, "/about/", about_page); 

	listen_http(serve);
	free_http(serve); // Освобождаем объект new_http
	return 0;
}

void index_page(int conn, HTTPreq *req) {
	if(strcmp(req->path, "/") != 0) {
		parsehtml_http(conn, "page404.html");
		return;
	}
	parsehtml_http(conn, "index.html"); //парсим сообщение и отправляем
}

void about_page(int conn, HTTPreq *req) {
	if(strcmp(req->path, "/about/") != 0) {
		parsehtml_http(conn, "page404.html");
		return;
	}
	parsehtml_http(conn, "about.html"); //парсим сообщение и отправляем
}
