#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>

bool FindWord(std::wstring sentence, std::wstring word)
{
    if (word.empty())
    {
        return false;
    }

    std::wstring separators = L" \t.,!?;:-()\"'«»—";
    size_t position = sentence.find(word);

    while (position != std::wstring::npos)
    {
        bool left = position == 0 || separators.find(sentence[position - 1]) != std::wstring::npos;
        bool right = position + word.size() == sentence.size() ||
            separators.find(sentence[position + word.size()]) != std::wstring::npos;

        if (left && right)
        {
            return true;
        }

        position = sentence.find(word, position + 1);
    }

    return false;
}

bool FindWordIgnoreCase(std::wstring sentence, std::wstring word)
{
    for (size_t i = 0; i < sentence.size(); i++)
    {
        if (sentence[i] >= L'A' && sentence[i] <= L'Z')
        {
            sentence[i] = sentence[i] + (L'a' - L'A');
        }
        else if (sentence[i] >= L'А' && sentence[i] <= L'Я')
        {
            sentence[i] = sentence[i] + (L'а' - L'А');
        }
        else if (sentence[i] == L'Ё')
        {
            sentence[i] = L'ё';
        }
    }

    for (size_t i = 0; i < word.size(); i++)
    {
        if (word[i] >= L'A' && word[i] <= L'Z')
        {
            word[i] = word[i] + (L'a' - L'A');
        }
        else if (word[i] >= L'А' && word[i] <= L'Я')
        {
            word[i] = word[i] + (L'а' - L'А');
        }
        else if (word[i] == L'Ё')
        {
            word[i] = L'ё';
        }
    }

    return FindWord(sentence, word);
}

int main()
{
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wstring original;
    std::wcout << L"Введите предложение: ";
    std::getline(std::wcin, original);

    std::wstring sentence = original;

    while (!sentence.empty() && (sentence[sentence.size() - 1] == L' ' || sentence[sentence.size() - 1] == L'\t'))
    {
        sentence.erase(sentence.size() - 1, 1);
    }

    if (sentence.empty())
    {
        std::wcout << L"Строка пустая!\n";
        return 0;
    }

    bool newWord = true;

    for (size_t i = 0; i < sentence.size(); i++)
    {
        wchar_t letter = sentence[i];

        if (letter >= L'A' && letter <= L'Z')
        {
            letter = letter + (L'a' - L'A');
        }
        else if (letter >= L'А' && letter <= L'Я')
        {
            letter = letter + (L'а' - L'А');
        }
        else if (letter == L'Ё')
        {
            letter = L'ё';
        }

        if (newWord)
        {
            if (letter >= L'a' && letter <= L'z')
            {
                letter = letter - (L'a' - L'A');
            }
            else if (letter >= L'а' && letter <= L'я')
            {
                letter = letter - (L'а' - L'А');
            }
            else if (letter == L'ё')
            {
                letter = L'Ё';
            }
        }

        sentence[i] = letter;

        if ((letter >= L'a' && letter <= L'z') ||
            (letter >= L'A' && letter <= L'Z') ||
            (letter >= L'а' && letter <= L'я') ||
            (letter >= L'А' && letter <= L'Я') ||
            letter == L'ё' || letter == L'Ё')
        {
            newWord = false;
        }
        else
        {
            newWord = true;
        }
    }

    if (sentence[sentence.size() - 1] != L'.')
    {
        sentence += L'.';
    }

    std::wcout << L"Результат: " << sentence << L"\n";

    std::wstring word;
    std::wcout << L"Введите слово для поиска: ";
    std::getline(std::wcin, word);

    if (FindWord(original, word))
    {
        std::wcout << L"Задание 4: слово найдено.\n";
    }
    else
    {
        std::wcout << L"Задание 4: слово не найдено.\n";
    }

    if (FindWordIgnoreCase(original, word))
    {
        std::wcout << L"Задание 5: слово найдено без учета регистра.\n";
    }
    else
    {
        std::wcout << L"Задание 5: слово не найдено без учета регистра.\n";
    }

    return 0;
}
