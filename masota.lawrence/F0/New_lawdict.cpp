#include "New_lawdict.h"

namespace dictcommands
{
    std::map< std::string, std::set<std::string> > input(std::istream& in)
    {
        std::vector< DictIO > dict;
        while (!in.eof())
        {
            std::copy(std::istream_iterator< DictIO >(in),
                std::istream_iterator< DictIO >(),
                std::back_inserter(dict));
            if (in.fail())
            {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        std::map< std::string, std::set<std::string> > input_dict;
        for (auto& el : dict)
        {
            input_dict[el.dict_el.first] = el.dict_el.second;
        }
        return input_dict;
    }
    void HELP(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        setlocale(LC_ALL, "Russian");
        if (in.get() == '\n')
        {
            out <<
                "##########################################" <<
                "###########################################\n" <<
                "Welcome to Lawrence's English-Russian dictionary :\n" <<
                "HELP command:\n" <<
                "1.'HELP' displays this script;\n" <<
                "2.'HELP COMMAND' displays the script from the description" <<
                "no built-in commands;\n" <<
                "3.'HELP INFO' displays the script with the description" <<
                "researching the open dictionary\n";
            out <<
                "###################################" <<
                "##################################################\n";
        }
        else
        {
            std::string argument;
            in >> argument;
            if (in.get() != '\n')
            {
                throw std::invalid_argument("<EXCESS ARGUMENT>");
            }
            if (argument == "COMMAND")
            {
                out <<
                    "#######################################" <<
                    "##############################################\n" <<
                    "Commands:\n" <<
                    "1.'HELP' - displays a list of commands available to the user.\n" <<
                    "2.'OPEN <path>' - open a file with" <<
                    "with a certain structure and reading into a dictionary.\n" <<
                    "3.'CLOSE <none/SAVE>' - closes the fa" <<
                    "whether saving changes or not" <<
                    "to the user's wishes.\n" <<
                    "4.'COMPARE <path>' - " <<
                    "reads a dictionary from a file and compares it" <<
                    "Only keys are repeated in two dictionaries.\n" <<
                    "5.'INSERT {<word> - <translation>}' - inserts into the dictionary but" <<
                    "your word and translation," <<
                    "if the key already exists, it completes the translation.\n" <<
                    "6.'DELETE <word>' - deletes a word and all translations from it.\n" <<
                    "7.'SEARCH <word>' - finds the word and word in the dictionary" <<
                    "if found or not found.\n" <<
                    "8.'CHANGE {<word> - <translation>}' - replacement" <<
                    "uses an existing key and translations" <<
                    "for a new one.\n" <<
                    "9.'SHOW <word>' - finds in words" <<
                    "are the word and displays all translations.\n" <<
                    "10.'SHOWALL' - displays the entire dictionary.\n";
                out <<
                    "##########################################" <<
                    "###########################################\n";
            }
            if (argument == "INFO")
            {
                out <<
                    "#path to dict: " << dict->first << "; size of dict: " << dict->second.size() << "#\n";
            }
        }
    }
    void OPEN(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (dict->first != "")
        {
            throw std::invalid_argument("<OLD DICT IS OPENED>");
        }
        if (in.get() == '\n')
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        std::string input_name;
        in >> input_name;
        std::ifstream input_file(input_name);
        if (!input_file)
        {
            throw std::invalid_argument("<CANT FIND FILE>");
        }
        if (in.get() != '\n')
        {
            throw std::invalid_argument("<EXCESS ARGUMENT>");
        }
        dict->first = input_name;
        dict->second = input(input_file);
        out << "#succeed#\n";
    }
    void CLOSE(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        std::string save = "N";
        if (in.get() != '\n')
        {
            in >> save;
            if (in.get() != '\n')
            {
                throw std::invalid_argument("<EXCESS ARGUMENT>");
            }
        }
        if (dict->first == "")
        {
            throw std::invalid_argument("<DICT ISNT OPEN>");
        }
        if (save == "SAVE")
        {
            std::ofstream output_file(dict->first);
            if (!output_file)
            {
                throw std::invalid_argument("<CANT FIND FILE>");
            }
            output_file.clear();
            for (auto pair = dict->second.begin(); pair != dict->second.end(); pair++)
            {
                output_file << "{" << pair->first << " -";
                for (auto trans = pair->second.begin(); trans != pair->second.end(); trans++)
                {
                    output_file << " " << trans->data();
                }
                output_file << "}\n";
            }
            out << "#close " << dict->first << " and save#\n";
        }
        else if (save != "N")
        {
            throw std::invalid_argument("<EXCESS ARGUMENT>");
        }
        else
        {
            out << "#close " << dict->first << "#\n";
        }
        dict->first = "";
        dict->second.clear();
    }
    void COMPARE(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (in.get() == '\n')
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        std::string input_name;
        in >> input_name;
        std::ifstream input_file(input_name);
        if (!input_file)
        {
            throw std::invalid_argument("<CANT FIND FILE>");
        }
        if (in.get() != '\n')
        {
            throw std::invalid_argument("<EXCESS ARGUMENT>");
        }
        std::map< std::string, std::set<std::string> > other_dict = input(input_file);
        std::size_t count = 0;
        for (auto this_pair = dict->second.begin(); this_pair != dict->second.end(); this_pair++)
        {
            for (auto other_pair = other_dict.begin(); other_pair != other_dict.end(); other_pair++)
            {
                if (this_pair->first == other_pair->first)
                {
                    count += 1;
                }
            }
        }
        out << "Identical keys: " << count << '\n';
    }
    void MERGE(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (in.get() == '\n')
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        std::string input_name;
        in >> input_name;
        std::ifstream input_file(input_name);
        if (!input_file)
        {
            throw std::invalid_argument("<CANT FIND FILE>");
        }
        if (in.get() != '\n')
        {
            throw std::invalid_argument("<EXCESS ARGUMENT>");
        }
        std::map< std::string, std::set<std::string> > other_dict = input(input_file);
        std::map< std::string, std::set<std::string> > this_dict = dict->second;
        for (auto other_pair = other_dict.begin(); other_pair != other_dict.end(); other_pair++)
        {
            if (this_dict.find(other_pair->first) == this_dict.cend())
            {
                dict->second[other_pair->first] = other_pair->second;
            }
        }
        out << "#succeed#\n";
    }
    void assign(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::string key, std::set<std::string> temp)
    {
        if (dict->second.find(key) == dict->second.cend())
        {
            dict->second[key] = temp;
        }
        else
        {
            dict->second.erase(key);
            dict->second[key] = temp;
        }
    }
    void INSERT(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (dict->first == "")
        {
            throw std::invalid_argument("<DICT ISNT OPEN>");
        }
        DictIO argument;
        in >> argument;
        if (in.fail())
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        std::set<std::string> temp = argument.dict_el.second;
        if (dict->second.count(argument.dict_el.first) != 0)
        {
            temp = dict->second[argument.dict_el.first];
        }
        for (auto other_argument = argument.dict_el.second.begin();
            other_argument != argument.dict_el.second.end(); other_argument++)
        {
            if (temp.find(*other_argument) == temp.cend())
            {
                temp.insert(*other_argument);
            }
        }
        assign(dict, argument.dict_el.first, temp);
        out << "#succeed#\n";
    }
    void DELETE(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (dict->first == "")
        {
            throw std::invalid_argument("<DICT ISNT OPEN>");
        }
        if (in.get() == '\n')
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        std::string key;
        in >> key;
        if (dict->second.count(key) == 1)
        {
            dict->second.erase(key);
            out << "#succed#\n";
        }
        else
        {
            out << "#not found#\n";
        }
    }
    void SEARCH(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (dict->first == "")
        {
            throw std::invalid_argument("<DICT ISNT OPEN>");
        }
        if (in.get() == '\n')
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        std::string key;
        in >> key;
        if (dict->second.count(key) == 1)
        {
            out << "#found#\n";
        }
        else
        {
            out << "#not found#\n";
        }
    }
    void CHANGE(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (dict->first == "")
        {
            throw std::invalid_argument("<DICT ISNT OPEN>");
        }
        DictIO argument;
        in >> argument;
        if (in.fail())
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        if (dict->second.count(argument.dict_el.first) != 1)
        {
            throw std::invalid_argument("<NO SUCH KEY>");
        }
        assign(dict, argument.dict_el.first, argument.dict_el.second);
        out << "#succeed#\n";
    }
    void SHOW(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (dict->first == "")
        {
            throw std::invalid_argument("<DICT ISNT OPEN>");
        }
        if (in.get() == '\n')
        {
            throw std::invalid_argument("<INVALID COMMANDS ARGUMENT>");
        }
        std::string key;
        in >> key;
        if (dict->second.count(key) == 1)
        {
            auto pair = dict->second.find(key);
            out << "{" << pair->first << " -";
            for (auto trans = pair->second.begin(); trans != pair->second.end(); trans++)
            {
                out << " " << trans->data();
            }
            out << "}\n";
        }
        else
        {
            out << "#not found#\n";
        }
    }
    void SHOWALL(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > > dict,
        std::istream& in, std::ostream& out)
    {
        if (dict->first == "")
        {
            throw std::invalid_argument("<DICT ISNT OPEN>");
        }
        if (in.get() != '\n')
        {
            throw std::invalid_argument("<EXCESS ARGUMENT>");
        }
        out << "#########################################" <<
            "############################################\n";
        for (auto pair = dict->second.begin(); pair != dict->second.end(); pair++)
        {
            out << "{" << pair->first << " -";
            for (auto trans = pair->second.begin(); trans != pair->second.end(); trans++)
            {
                out << " " << trans->data();
            }
            out << "}\n";
        }
        out << "####################################" <<
            "#################################################\n";
    }
}
