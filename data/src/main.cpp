#define SDL_MAIN_HANDLED
#include "lgs/lgasm.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

vector<string> split_token(string s, char del)
{
    vector<string> words;
    stringstream ss(s);
    string word;

    while (!ss.eof()) 
    {
        getline(ss, word, del);
        words.push_back(word);
    }

    return words;
}

vector<vector<vector<string>>> splitter(string text)
{
    vector<vector<string>> startLoop;
    vector<vector<string>> updateLoop;

    vector<string> lines = split_token(text, '\n');

    bool lgasmScript = false;
    bool write = false;
    string whatNeedToWrite = "";

    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> lineNoTabs = split_token(lines[i], '\t');
        vector<string> words = split_token(lineNoTabs[0], ' ');

        if (words[0] == "at" && !lgasmScript)
        {
            if (words[1] == "LGASM")
            {
                lgasmScript = true;
            }
            else
            {
                cout << "not lgasm script\n";
            }
        }
        else if (lgasmScript)
        {
            if (write)
            {
                
                if (whatNeedToWrite == "start")
                {
                    if (words[0] == ":")
                    {
                        write = false;
                        whatNeedToWrite = "";
                        i++;
                    }
                    startLoop.push_back(words);
                }
                else if (whatNeedToWrite == "update")
                {
                    if (words[0] == ":")
                    {
                        write = false;
                        whatNeedToWrite = "";
                        i++;
                    }
                    updateLoop.push_back(words);
                }
            }
            else if (words[0] == ".start")
            {
                write = true;
                whatNeedToWrite = "start";
            }
            else if (words[0] == ".update")
            {
                write = true;
                whatNeedToWrite = "update";
            }
        }
        else
        {
            cout << "undefined script type\n";
        }
    }

    vector<vector<vector<string>>> data;
    data.push_back(startLoop);
    data.push_back(updateLoop);

    return data;
}

#define LGS_WT "wt"
#define LGS_CLS "cls"
#define LGS_RCT "rct"
#define LGS_BLT "blt"
#define LGS_SPX "spx"
#define LGS_NMBR "nmbr"
#define LGS_ADN "adn"
#define LGS_DLY "dly"
#define LGS_ONKEY "onkey"

uLG_Color LGRED = (uLG_Color){255, 0, 0};
uLG_Color LGGREEN = (uLG_Color){0, 255, 0};
uLG_Color LGBLUE = (uLG_Color){0, 0, 255};
uLG_Color LGWHITE = (uLG_Color){255, 255, 255};
uLG_Color LGGRAY = (uLG_Color){125, 125, 125};
uLG_Color LGBLACK = (uLG_Color){0, 0, 0};

int parser(vector<vector<vector<string>>> data)
{
    vector<vector<string>> start = data[0];
    vector<vector<string>> update = data[1];

    LG_Window window;

    map<string, LG_Rect*> rectList;
    map<string, int> numberList;

    map<string, int> keyList;
    keyList["q"] = SDL_SCANCODE_Q;
    keyList["w"] = SDL_SCANCODE_W;
    keyList["e"] = SDL_SCANCODE_E;
    keyList["r"] = SDL_SCANCODE_R;
    keyList["t"] = SDL_SCANCODE_T;
    keyList["y"] = SDL_SCANCODE_Y;
    keyList["u"] = SDL_SCANCODE_U;
    keyList["i"] = SDL_SCANCODE_I;
    keyList["o"] = SDL_SCANCODE_O;
    keyList["p"] = SDL_SCANCODE_P;
    keyList["a"] = SDL_SCANCODE_A;
    keyList["s"] = SDL_SCANCODE_S;
    keyList["d"] = SDL_SCANCODE_D;
    keyList["f"] = SDL_SCANCODE_F;
    keyList["g"] = SDL_SCANCODE_G;
    keyList["h"] = SDL_SCANCODE_H;
    keyList["j"] = SDL_SCANCODE_J;
    keyList["k"] = SDL_SCANCODE_K;
    keyList["l"] = SDL_SCANCODE_L;
    keyList["z"] = SDL_SCANCODE_Z;
    keyList["x"] = SDL_SCANCODE_X;
    keyList["c"] = SDL_SCANCODE_C;
    keyList["v"] = SDL_SCANCODE_V;
    keyList["q"] = SDL_SCANCODE_B;
    keyList["n"] = SDL_SCANCODE_N;
    keyList["m"] = SDL_SCANCODE_M;

    map<string, uLG_Color> colorList;
    colorList["RED"] = LGRED;
    colorList["GREEN"] = LGGREEN;
    colorList["BLUE"] = LGBLUE;
    colorList["WHITE"] = LGWHITE;
    colorList["GRAY"] = LGGRAY;
    colorList["BLACK"] = LGBLACK;

    for (int i = 0; i < start.size(); i++)
    {
        vector<string> words = start[i];

        if (words[0] == LGS_WT)
        {
            window.SetData(words[1].c_str());
        }
        else if (words[0] == LGS_NMBR)
        {
            numberList[words[1]] = stoi(words[2]);
        }
    }

    while (window.IsOpen)
    {
        for (int i = 0; i < update.size(); i++)
        {
            vector<string> words = update[i];

            if (words[0] == LGS_CLS)
            {
                if (words.size() == 4)
                {
                    uLG_Color color = {stoi(words[1]), stoi(words[2]), stoi(words[3])};
                    window.Clear(&color);
                }
                else
                {
                    window.Clear(&colorList[words[1]]);
                }
            }
            // else if (words[0] == LGS_BLT)
            // {
            //     LG_Rect* rect = rectList[words[1]];
            //     uLG_Color color = colorList[words[2]];
            //     // SDL_Rect* _rect = rect->GetRect();
            //     // cout << _rect->x << _rect->y << _rect->w << _rect->h << endl;
            //     window.Draw(rect, &color);
            // }
            else if (words[0] == LGS_SPX)
            {
                int x, y;
                if (words[1].c_str()[0] == '$')
                {
                    x = numberList[words[1].replace(0, 1, "")];
                    if (words[2].c_str()[0] == '$')
                    {
                        y = numberList[words[2].replace(0, 1, "")];
                    }
                    else
                    {
                        y = stoi(words[2]);
                    }
                }
                else if (words[2].c_str()[0] == '$')
                {
                    x = stoi(words[1]);
                    y = numberList[words[2].replace(0, 1, "")];
                }
                else
                {
                    x = stoi(words[1]);
                    y = stoi(words[2]);
                }

                LG_Rect rect = LG_Rect(x, y, 1, 1);

                uLG_Color color;
                if (words.size() == 6)
                {
                    color = {stoi(words[3]), stoi(words[4]), stoi(words[5])};
                }
                else
                {
                    color = colorList[words[3]];
                }

                window.Draw(&rect, &color);
            }
            else if (words[0] == LGS_ADN)
            {
                numberList[words[1]] += stoi(words[2]);
            }
            else if (words[0] == LGS_DLY)
            {
                window.Delay(stoi(words[1]));
            }
            else if (words[0] == LGS_ONKEY)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if (state[keyList[words[1]]])
                {
                    vector<string> onKeyWords;
                    for (int j = 2; j < words.size(); j++)
                    {
                        onKeyWords.push_back(words[j]);
                    }

                    if (onKeyWords[0] == LGS_CLS)
                    {
                        if (onKeyWords.size() == 4)
                        {
                            uLG_Color color = {stoi(onKeyWords[1]), stoi(onKeyWords[2]), stoi(onKeyWords[3])};
                            window.Clear(&color);
                        }
                        else
                        {
                            window.Clear(&colorList[onKeyWords[1]]);
                        }
                    }
                    // else if (onKeyWords[0] == LGS_BLT)
                    // {
                    //     LG_Rect* rect = rectList[onKeyWords[1]];
                    //     uLG_Color color = colorList[onKeyWords[2]];
                    //     // SDL_Rect* _rect = rect->GetRect();
                    //     // cout << _rect->x << _rect->y << _rect->w << _rect->h << endl;
                    //     window.Draw(rect, &color);
                    // }
                    else if (onKeyWords[0] == LGS_SPX)
                    {
                        int x, y;
                        if (onKeyWords[1].c_str()[0] == '$')
                        {
                            x = numberList[onKeyWords[1].replace(0, 1, "")];
                            if (onKeyWords[2].c_str()[0] == '$')
                            {
                                y = numberList[onKeyWords[2].replace(0, 1, "")];
                            }
                            else
                            {
                                y = stoi(onKeyWords[2]);
                            }
                        }
                        else if (onKeyWords[2].c_str()[0] == '$')
                        {
                            x = stoi(onKeyWords[1]);
                            y = numberList[onKeyWords[2].replace(0, 1, "")];
                        }
                        else
                        {
                            x = stoi(onKeyWords[1]);
                            y = stoi(onKeyWords[2]);
                        }

                        LG_Rect rect = LG_Rect(x, y, 1, 1);

                        uLG_Color color;
                        if (onKeyWords.size() == 6)
                        {
                            color = {stoi(onKeyWords[3]), stoi(onKeyWords[4]), stoi(onKeyWords[5])};
                        }
                        else
                        {
                            color = colorList[onKeyWords[3]];
                        }

                        window.Draw(&rect, &color);
                    }
                    else if (onKeyWords[0] == LGS_ADN)
                    {
                        numberList[onKeyWords[1]] += stoi(onKeyWords[2]);
                    }
                    else if (onKeyWords[0] == LGS_DLY)
                    {
                        window.Delay(stoi(onKeyWords[1]));
                    }
                }
            }
        }
        window.Update();
        window.PollEvent();
    }

    return 0;
}

int main(int argc, char** argv)
{
    fstream file(argv[1]);
    stringstream buf;
    buf << file.rdbuf();

    string text = buf.str();

    vector<vector<vector<string>>> data = splitter(text);
    int succes = parser(data);
}