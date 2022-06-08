#ifdef __unix__         //https://stackoverflow.com/questions/8764295/undefined-reference-to-sleep-but-i-did-include-unistd-h
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <conio.h>
#include <fstream>

using namespace std;

//ispisuje naslov igre

void title()
{
    cout << "  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\n";
    cout << "     \xDB\xDB    \xDB\xDB         \xDB\xDB    \xDB\xDB   \xDB\xDB \xDB\xDB \xDB\xDB     \n";
    cout << "     \xDB\xDB    \xDB\xDB\xDB\xDB\xDB      \xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\n";
    cout << "     \xDB\xDB    \xDB\xDB         \xDB\xDB    \xDB\xDB   \xDB\xDB \xDB\xDB      \xDB\xDB\n";
    cout << "     \xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB    \xDB\xDB   \xDB\xDB \xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\n";
}

//provjerava jeli igra gotova

bool endgame(string polje[26][16]) //endgame(poljekopija)
{
    string x = "\xDB";
    int z = 1;
    if (polje[2][1] == x || polje[2][2] == x || polje[2][3] == x || polje[2][4] == x || polje[2][5] == x || polje[2][6] == x || polje[2][7] == x || polje[2][8] == x || polje[2][9] == x || polje[2][10] == x || polje[2][11] == x || polje[2][12] == x || polje[2][13] == x || polje[2][14] == x)
    {
        return true;
    }
    else
        return false;
}


//cisti ekran bez treperenja (kopirano s neta "https://www.sololearn.com/Discuss/1714796/how-to-update-console-without-flicker-in-c")

void ClearScreen()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
//konstrucktor default polja
void constructtetrisdefault(int i, int j, int visina, int sirina, string polje[26][16]) //constructtetrisdefault(i, j, visina, sirina, polje)
{
    for (i = 0; i < visina; i++)
    {
        for (j = 0; j < sirina; j++)
        {
            if (i == 0)
            {
                polje[i][j] = '\xDC';
            }
            else if (i == visina - 1)
            {
                polje[i][j] = '\xDF';
            }
            else if (j == 0 || j == sirina - 1)
            {
                polje[i][j] = "\xDB";
            }
            else
            {
                polje[i][j] = " ";

            }

        }
    }
}

void constructtetriscopydefault(int i, int j, int visina, int sirina, string poljekopija[26][16]) //constructtetriscopydefault(i, j, visina, sirina, poljekopija)
{
    for (i = 0; i < visina; i++)
    {
        for (j = 0; j < sirina; j++)
        {
            poljekopija[i][j] = " ";

        }
    }
}
//konstrucktor polja
void constructtetris(int i, int j, int visina, int sirina, string polje[26][16], string poljekopija[26][16]) //constructtetris(i, j, visina, sirina, polje, poljekopija);
{
    for (i = 0; i < visina; i++)
    {
        for (j = 0; j < sirina; j++)
        {
            if (i == 0)
            {
                polje[i][j] = '\xDC';
            }
            else if (i == visina - 1)
            {
                polje[i][j] = '\xDF';
            }
            else if (j == 0 || j == sirina - 1)
            {
                polje[i][j] = "\xDB";
            }
            else
            {
                polje[i][j] = " ";

            }

        }
    }
    for (i = 0; i < visina; ++i)
    {
        for (j = 0; j < sirina; ++j)
        {
            if (poljekopija[i][j] == "\xDB")
            {
                polje[i][j] = "\xDB";
            }
        }
    }
}

//update frame

void drawtetris(int visina, int sirina, string polje[26][16], string poljekopija[26][16]) //drawtetris(visina, sirina, polje, poljekopija);
{
    int i, j;
    for (i = 0; i < visina; ++i)
    {
        for (j = 0; j < sirina; ++j)
        {
            if (poljekopija[i][j] == "\xDB")
            {
                polje[i][j] = poljekopija[i][j];
            }
        }
    }
    for (i = 0; i < visina; ++i)
    {
        for (j = 0; j < sirina; ++j)
        {
            cout << polje[i][j];
        }
        cout << endl;
    }

}

//zapamti polje
void pamti(const int visina, const int sirina, string polje[26][16], string poljekopija[26][16])//pamti(visina, sirina, polje, poljekopija);
{
    int i, j;
    for (i = 0; i < visina; ++i)
    {
        for (j = 0; j < sirina; ++j)
        {
            if (polje[i][j] == "\xDB")
            {
                poljekopija[i][j] = polje[i][j];
            }
        }
    }
}


// cisti pun red

void cistired(string poljekopija[26][16], long long int score) //cistired(poljekopija);
{
    string x = "\xDB";
    int i, j;
    int k, l;
    for (int n = 0; n < 25; n++)
    {
        for (i = 24; i > 1; i--)
        {
            for (j = 1; j < 15; j++)
            {
                if (poljekopija[i][j] == x)
                {
                    if (j == 14)
                    {
                        k = i;
                        for (k; k > 1; k--)
                        {
                            for (l = 1; l < 15; l++)
                            {
                                poljekopija[k][l] = poljekopija[k - 1][l];
                            }
                        }
                    }
                }
                else
                    break;
            }
        }
    }
}

//structs

struct bojapoz {
    //  j   i
    int a, a1;
    int b, b1;
    int c, c1;
    int d, d1;
} aquapoz, plavapoz, narandastapoz, zutapoz, zelenapoz, ljubicastapoz, crvenapoz;


// oblici

bool checkifrotationstick(bojapoz aquapoz, bool horizontalno, string polje[26][16]) //checkifrotationstick(aquapoz, horizontalno, polje)
{
    if (horizontalno == true)
    {
        if (aquapoz.a1 != 1 && aquapoz.b1 != 1 && aquapoz.c1 != 1 && aquapoz.d1 != 1 && aquapoz.a1 != 23 && aquapoz.b1 != 23 && aquapoz.c1 != 23 && aquapoz.d1 != 23 && aquapoz.a1 != 24 && aquapoz.b1 != 24 && aquapoz.c1 != 24 && aquapoz.d1 != 24)
        {
            if (polje[aquapoz.a1 - 2][aquapoz.a + 2] == "\xDB" || polje[aquapoz.b1 - 1][aquapoz.b + 1] == "\xDB" || polje[aquapoz.d1 + 1][aquapoz.d - 1] == "\xDB" || polje[aquapoz.a1 + 2][aquapoz.a] == "\xDB" || polje[aquapoz.b1 + 2][aquapoz.b] == "\xDB" || polje[aquapoz.d1 + 2][aquapoz.d] == "\xDB")
            {
                return false;
            }
            else
                return true;
        }
        else
            return true;
    }
    else
    {
        if (aquapoz.a != 1 && aquapoz.b != 1 && aquapoz.c != 1 && aquapoz.d != 1 && aquapoz.a != 2 && aquapoz.b != 2 && aquapoz.c != 2 && aquapoz.d != 2 && aquapoz.a != 14 && aquapoz.b != 14 && aquapoz.c != 14 && aquapoz.d != 14)
        {
            if (polje[aquapoz.a1 + 2][aquapoz.a - 2] == "\xDB" || polje[aquapoz.b1 + 1][aquapoz.b - 1] == "\xDB" || polje[aquapoz.d1 - 1][aquapoz.d + 1] == "\xDB")
            {
                return false;
            }
            else
                return true;
        }
        else
            return true;
    }
}



bool checkifstick(bool horizontalno, bojapoz aquapoz, string polje[26][16]) //checkifstick(horizontalno, aquapoz, polje)
{
    string x = " ";
    if (horizontalno == true)
    {
        if (polje[aquapoz.a1 + 1][aquapoz.a] != x || polje[aquapoz.b1 + 1][aquapoz.b] != x || polje[aquapoz.c1 + 1][aquapoz.c] != x || polje[aquapoz.d1 + 1][aquapoz.d] != x)
        {
            return false;
        }
        else
            return true;
    }
    else
    {
        if (polje[aquapoz.d1 + 1][aquapoz.d] != x)
        {
            return false;
        }
        else
            return true;
    }
}

bool checkifleft(bojapoz aquapoz, string polje[26][16]) //checkifleft(aquapoz, polje)
{
    string x = " ";
    bool leftestA1 = false;
    bool leftestB1 = false;
    bool leftestC1 = false;
    bool leftestD1 = false;
    short int leftflagA = 1;
    short int leftflagB = 1;
    short int leftflagC = 1;
    short int leftflagD = 1;


    if (polje[aquapoz.a1][aquapoz.a - 1] == polje[aquapoz.b1][aquapoz.b] || polje[aquapoz.a1][aquapoz.a - 1] == polje[aquapoz.c1][aquapoz.c] || polje[aquapoz.a1][aquapoz.a - 1] == polje[aquapoz.d1][aquapoz.d])
    {
        leftestA1 = false;
    }
    else
    {
        leftestA1 = true;
    }
    if (polje[aquapoz.b1][aquapoz.b - 1] == polje[aquapoz.a1][aquapoz.a] || polje[aquapoz.b1][aquapoz.b - 1] == polje[aquapoz.c1][aquapoz.c] || polje[aquapoz.b1][aquapoz.b - 1] == polje[aquapoz.d1][aquapoz.d])
    {
        leftestB1 = false;
    }
    else
    {
        leftestB1 = true;
    }
    if (polje[aquapoz.c1][aquapoz.c - 1] == polje[aquapoz.b1][aquapoz.b] || polje[aquapoz.c1][aquapoz.c - 1] == polje[aquapoz.a1][aquapoz.a] || polje[aquapoz.c1][aquapoz.c - 1] == polje[aquapoz.d1][aquapoz.d])
    {
        leftestC1 = false;
    }
    else
    {
        leftestC1 = true;
    }
    if (polje[aquapoz.d1][aquapoz.d - 1] == polje[aquapoz.b1][aquapoz.b] || polje[aquapoz.d1][aquapoz.d - 1] == polje[aquapoz.c1][aquapoz.c] || polje[aquapoz.d1][aquapoz.d - 1] == polje[aquapoz.a1][aquapoz.a])
    {
        leftestD1 = false;
    }
    else
    {
        leftestD1 = true;
    }
    if (leftestA1 == true)
    {
        if (polje[aquapoz.a1][aquapoz.a - 1] == x)
        {
            leftflagA = 1;
        }
        else
        {
            leftflagA = 0;
        }
    }
    if (leftestB1 == true)
    {
        if (polje[aquapoz.b1][aquapoz.b - 1] == x)
        {
            leftflagB = 1;
        }
        else
        {
            leftflagB = 0;
        }
    }
    if (leftestC1 == true)
    {
        if (polje[aquapoz.c1][aquapoz.c - 1] == x)
        {
            leftflagC = 1;
        }
        else
        {
            leftflagC = 0;
        }
    }
    if (leftestD1 == true)
    {
        if (polje[aquapoz.d1][aquapoz.d - 1] == x)
        {
            leftflagD = 1;
        }
        else
        {
            leftflagD = 0;
        }
    }



    if (leftflagA == 1 && leftflagB == 1 && leftflagC == 1 && leftflagD == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkifright(bojapoz aquapoz, string polje[26][16]) //checkifright(aquapoz, polje)
{
    string x = " ";
    bool rightestA1 = false;
    bool rightestB1 = false;
    bool rightestC1 = false;
    bool rightestD1 = false;
    short int rightflagA = 1;
    short int rightflagB = 1;
    short int rightflagC = 1;
    short int rightflagD = 1;

    if (polje[aquapoz.a1][aquapoz.a + 1] == polje[aquapoz.b1][aquapoz.b] || polje[aquapoz.a1][aquapoz.a + 1] == polje[aquapoz.c1][aquapoz.c] || polje[aquapoz.a1][aquapoz.a + 1] == polje[aquapoz.d1][aquapoz.d])
    {
        rightestA1 = false;
    }
    else
    {
        rightestA1 = true;
    }
    if (polje[aquapoz.b1][aquapoz.b + 1] == polje[aquapoz.a1][aquapoz.a] || polje[aquapoz.b1][aquapoz.b + 1] == polje[aquapoz.c1][aquapoz.c] || polje[aquapoz.b1][aquapoz.b + 1] == polje[aquapoz.d1][aquapoz.d])
    {
        rightestB1 = false;
    }
    else
    {
        rightestB1 = true;
    }
    if (polje[aquapoz.c1][aquapoz.c + 1] == polje[aquapoz.b1][aquapoz.b] || polje[aquapoz.c1][aquapoz.c + 1] == polje[aquapoz.a1][aquapoz.a] || polje[aquapoz.c1][aquapoz.c + 1] == polje[aquapoz.d1][aquapoz.d])
    {
        rightestC1 = false;
    }
    else
    {
        rightestC1 = true;
    }
    if (polje[aquapoz.d1][aquapoz.d + 1] == polje[aquapoz.b1][aquapoz.b] || polje[aquapoz.d1][aquapoz.d + 1] == polje[aquapoz.c1][aquapoz.c] || polje[aquapoz.d1][aquapoz.d + 1] == polje[aquapoz.a1][aquapoz.a])
    {
        rightestD1 = false;
    }
    else
    {
        rightestD1 = true;
    }
    if (rightestA1 == true)
    {
        if (polje[aquapoz.a1][aquapoz.a + 1] == x)
        {
            rightflagA = 1;
        }
        else
        {
            rightflagA = 0;
        }
    }
    if (rightestB1 == true)
    {
        if (polje[aquapoz.b1][aquapoz.b + 1] == x)
        {
            rightflagB = 1;
        }
        else
        {
            rightflagB = 0;
        }
    }
    if (rightestC1 == true)
    {
        if (polje[aquapoz.c1][aquapoz.c + 1] == x)
        {
            rightflagC = 1;
        }
        else
        {
            rightflagC = 0;
        }
    }
    if (rightestD1 == true)
    {
        if (polje[aquapoz.d1][aquapoz.d + 1] == x)
        {
            rightflagD = 1;
        }
        else
        {
            rightflagD = 0;
        }
    }

    if (rightflagA == 1 && rightflagB == 1 && rightflagC == 1 && rightflagD == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main()
{
    // kontrola konzole u svrhu mjenjanja boje
    HANDLE konzola = GetStdHandle(STD_OUTPUT_HANDLE);
    // boja text
    int aqua = 3;
    int plava = 1;
    int bjela = 15;
    int siva = 8;
    // colorattribute = predzadina + pozadina * 16
    int crnonabjelo = 240;
    int bjelonacrno = 15;
    int sivonabjelo = 248;
    // dimenzije tetris polja
    const int visina = 26; //19
    const int sirina = 16; //14
    string polje[visina][sirina];
    string poljekopija[visina][sirina];
    //ostale varijable
    long long int highscore = 0;
    short int selektor = 0;
    int tipka;
    int i = 0, j = 0;
    bool menu = true;
    float brzina = 0.3;
    long long int score = 0;
    int random;
    //oblici booleans
    bool stick = false;
    bool Lleft = false;
    bool Lright = false;
    bool cube = false;
    bool Dogleft = false;
    bool Dogright = false;
    bool T = false;
    bool jednom = true;
    bool save = false;
    //rotacija
    bool horizontalno = true;
    //konstruktor polja
    constructtetris(i, j, visina, sirina, polje, poljekopija);
    //highscore load system
    ifstream filescore("highscore.bin", ios::binary);
    filescore.read((char*)&highscore, sizeof(highscore));
    filescore.close();
    while (1)
    {
        //provjerava postoji li sejvan gejm
        ifstream filetetris;
        filetetris.open("tetrispolje.bin");
        if (filetetris)
        {
            save = true;
        }
        else
        {
            save = false;
        }
        filetetris.close();
        //glavni menu
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        system("cls");
        while (menu == true)
        {
            constructtetrisdefault(i, j, visina, sirina, polje);
            constructtetriscopydefault(i, j, visina, sirina, poljekopija);
            SetConsoleTextAttribute(konzola, bjela);
            cout << endl;
            title();
            cout << endl;
            cout << "                  HIGHSCORE: " << highscore << endl;
            if (selektor == 0)
            {
                if (save == true)
                {
                    SetConsoleTextAttribute(konzola, crnonabjelo);
                    cout << "  << New Game >>" << endl;
                    SetConsoleTextAttribute(konzola, bjela);
                    cout << "     Continue" << endl;
                    SetConsoleTextAttribute(konzola, bjelonacrno);
                    cout << "     Exit" << endl;
                }
                else
                {
                    SetConsoleTextAttribute(konzola, crnonabjelo);
                    cout << "  << New Game >>" << endl;
                    SetConsoleTextAttribute(konzola, siva);
                    cout << "     Continue" << endl;
                    SetConsoleTextAttribute(konzola, bjelonacrno);
                    cout << "     Exit" << endl;
                }
            }
            if (selektor == 1)
            {
                if (save == true)
                {
                    SetConsoleTextAttribute(konzola, bjela);
                    cout << "     New Game" << endl;
                    SetConsoleTextAttribute(konzola, crnonabjelo);
                    cout << "  << Continue >>" << endl;
                    SetConsoleTextAttribute(konzola, bjelonacrno);
                    cout << "     Exit" << endl;
                }
                else
                {
                    SetConsoleTextAttribute(konzola, bjela);
                    cout << "     New Game" << endl;
                    SetConsoleTextAttribute(konzola, sivonabjelo);
                    cout << "  << Continue >>" << endl;
                    SetConsoleTextAttribute(konzola, bjelonacrno);
                    cout << "     Exit" << endl;
                }
            }
            if (selektor == 2)
            {
                if (save == true)
                {
                    SetConsoleTextAttribute(konzola, bjela);
                    cout << "     New Game" << endl;
                    SetConsoleTextAttribute(konzola, bjela);
                    cout << "     Continue" << endl;
                    SetConsoleTextAttribute(konzola, crnonabjelo);
                    cout << "  << Exit >>" << endl;
                    SetConsoleTextAttribute(konzola, bjela);
                }
                else
                {
                    SetConsoleTextAttribute(konzola, bjela);
                    cout << "     New Game" << endl;
                    SetConsoleTextAttribute(konzola, siva);
                    cout << "     Continue" << endl;
                    SetConsoleTextAttribute(konzola, crnonabjelo);
                    cout << "  << Exit >>" << endl;
                    SetConsoleTextAttribute(konzola, bjela);
                }
            }
            tipka = _getch();
            if (tipka == 'w' || tipka == 72)
            {
                selektor = selektor - 1;
            }
            if (tipka == 's' || tipka == 80)
            {
                selektor = selektor + 1;
            }
            if (GetKeyState(VK_RETURN) & 0x8000)
            {
                if (selektor == 2)
                {
                    return 0;
                }
                else if (selektor == 1 && save == true)
                {
                    ifstream filetetris("tetrispolje.bin", ios::binary);
                    for (i = 0; i < 26; i++)
                    {
                        for (j = 0; j < 16; j++)
                        {
                            filetetris.read((char*)&poljekopija[i][j], visina * sirina * sizeof(char));
                        }
                    }
                    filetetris.close();
                    menu = false;
                }
                else if (selektor == 0)
                {
                    menu = false;
                }
            }
            if (selektor > 2)
            {
                selektor = selektor - 3;
            }
            if (selektor < 0)
            {
                selektor = selektor + 3;
            }
            system("cls");
        }//kraj menu
        //generate shape
        horizontalno = true;
        bool stick = false;
        bool Lleft = false;
        bool Lright = false;
        bool cube = false;
        bool Dogleft = false;
        bool Dogright = false;
        bool T = false;
        bool jednom = true;
        bool bsave = false;
        std::srand(time(0));
        random = 1 + rand() % 7;
        random = 1;
        if (random == 1)
        {
            stick = true;
            aquapoz.a1 = 1, aquapoz.a = 6;
            aquapoz.b1 = 1, aquapoz.b = 7;
            aquapoz.c1 = 1; aquapoz.c = 8;
            aquapoz.d1 = 1, aquapoz.d = 9;

        }
        else if (random == 2)
        {
            Lleft = true;
        }
        else if (random == 3)
        {
            Lright = true;
        }
        else if (random == 4)
        {
            cube = true;
        }
        else if (random == 5)
        {
            Dogright = true;
        }
        else if (random == 6)
        {
            T = true;
        }
        else if (random == 7)
        {
            Dogleft = true;
        }
        // ---------------
        if (stick == true)
        {
            while (1)
            {
                if (checkifstick(horizontalno, aquapoz, polje) == true)
                {
                    constructtetris(i, j, visina, sirina, polje, poljekopija);

                    //rotacija
                    if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
                    {
                        if (checkifrotationstick(aquapoz, horizontalno, polje) == true)
                        {
                            if (horizontalno == true)
                            {
                                if (aquapoz.a1 == 1 || aquapoz.b1 == 1 || aquapoz.c1 == 1 || aquapoz.d1 == 1)
                                {
                                    aquapoz.a1++;
                                    aquapoz.b1++;
                                    aquapoz.c1++;
                                    aquapoz.d1++;
                                }
                                if (aquapoz.a1 == 23 || aquapoz.b1 == 23 || aquapoz.c1 == 23 || aquapoz.d1 == 23)
                                {
                                    aquapoz.a1--;
                                    aquapoz.b1--;
                                    aquapoz.c1--;
                                    aquapoz.d1--;
                                }
                                if (aquapoz.a1 == 24 || aquapoz.b1 == 24 || aquapoz.c1 == 24 || aquapoz.d1 == 24)
                                {
                                    aquapoz.a1 = aquapoz.a1 - 2;
                                    aquapoz.b1 = aquapoz.b1 - 2;
                                    aquapoz.c1 = aquapoz.c1 - 2;
                                    aquapoz.d1 = aquapoz.d1 - 2;
                                }
                                aquapoz.a1 = aquapoz.a1 - 2;
                                aquapoz.b1 = aquapoz.b1 - 1;
                                aquapoz.d1 = aquapoz.d1 + 1;

                                aquapoz.a = aquapoz.a + 2;
                                aquapoz.b = aquapoz.b + 1;
                                aquapoz.d = aquapoz.d - 1;
                                horizontalno = false;
                            }
                            else if (horizontalno == false)
                            {
                                if (aquapoz.a == 1 || aquapoz.b == 1 || aquapoz.c == 1 || aquapoz.d == 1)
                                {
                                    aquapoz.a = aquapoz.a + 2;
                                    aquapoz.b = aquapoz.b + 2;
                                    aquapoz.c = aquapoz.c + 2;
                                    aquapoz.d = aquapoz.d + 2;
                                }
                                if (aquapoz.a == 2 || aquapoz.b == 2 || aquapoz.c == 2 || aquapoz.d == 2)
                                {
                                    aquapoz.a++;
                                    aquapoz.b++;
                                    aquapoz.c++;
                                    aquapoz.d++;
                                }
                                if (aquapoz.a == 14 || aquapoz.b == 14 || aquapoz.c == 14 || aquapoz.d == 14)
                                {
                                    aquapoz.a--;
                                    aquapoz.b--;
                                    aquapoz.c--;
                                    aquapoz.d--;
                                }
                                aquapoz.a1 = aquapoz.a1 + 2;
                                aquapoz.b1 = aquapoz.b1 + 1;
                                aquapoz.d1 = aquapoz.d1 - 1;

                                aquapoz.a = aquapoz.a - 2;
                                aquapoz.b = aquapoz.b - 1;
                                aquapoz.d = aquapoz.d + 1;
                                horizontalno = true;
                            }
                        }
                    }
                    //ljevodesno
                    if (checkifleft(aquapoz, polje) == true)
                    {
                        if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
                        {
                            aquapoz.a--;
                            aquapoz.b--;
                            aquapoz.c--;
                            aquapoz.d--;

                        }
                    }
                    if (checkifright(aquapoz, polje) == true)
                    {
                        if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
                        {
                            aquapoz.a++;
                            aquapoz.b++;
                            aquapoz.c++;
                            aquapoz.d++;
                        }
                    }
                    if (GetAsyncKeyState(VK_SPACE))
                    {
                        brzina = 0.03;
                    }
                    else
                        brzina = 0.3;
                    //padanje
                    if (jednom == true)
                    {
                        polje[aquapoz.a1][aquapoz.a] = "\xDB";
                        polje[aquapoz.b1][aquapoz.b] = "\xDB";
                        polje[aquapoz.c1][aquapoz.c] = "\xDB";
                        polje[aquapoz.d1][aquapoz.d] = "\xDB";
                        jednom = false;
                    }
                    else
                    {
                        aquapoz.a1++;
                        aquapoz.b1++;
                        aquapoz.c1++;
                        aquapoz.d1++;
                        polje[aquapoz.a1][aquapoz.a] = "\xDB";
                        polje[aquapoz.b1][aquapoz.b] = "\xDB";
                        polje[aquapoz.c1][aquapoz.c] = "\xDB";
                        polje[aquapoz.d1][aquapoz.d] = "\xDB";
                    }
                    drawtetris(visina, sirina, polje, poljekopija);
                    ClearScreen();
                    sleep(brzina);
                }
                else
                {
                    pamti(visina, sirina, polje, poljekopija);
                    cistired(poljekopija, score);
                    score = score + 125;
                    horizontalno = true;
                    stick = false;
                    jednom = true;
                    ofstream filetetris("tetrispolje.bin", ios::binary);
                    for (i = 0; i < 26; i++)
                    {
                        for (j = 0; j < 16; j++)
                        {
                            filetetris.write((char*)&poljekopija[i][j], visina * sirina * sizeof(char));
                        }
                    }
                    filetetris.close();
                    if (score > highscore)
                    {
                        highscore = score;
                        ofstream filescore("highscore.bin", ios::binary);
                        filescore.write((char*)&highscore, sizeof(highscore));
                        filescore.close();
                    }
                    if (endgame(polje) == true)
                    {
                        score = 0;
                        menu = true;
                        remove("tetrispolje.bin");
                        break;
                    }
                    else
                        break;
                }
            }
        }
    }

    return 0;
}
