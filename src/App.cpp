#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "App.hpp"

// Définition des menus
bool App::MenuPrincipal()
{
    this->banner("Bienvenue dans AirWatcher", true);
    this->userbar("(anonyme)");
    std::cout << std::endl;

    // Tous les menus
    const std::vector<std::string> menuPrincipal = {"Vos données…", "Analyse…", "Sources de données…", "Administration…", "Quitter AirWatcher"};

    while (true)
    {
        const int choice = this->menu("Menu Principal", menuPrincipal);

        switch (choice)
        {
        case App::InvalidMenuChoice:
            std::cout << "Vous n'avez pas choisi de menu." << std::endl;
            return false;
            break;

        default:
            std::cout << "Choix #" << choice << std::endl;
            // return true;
            break;
        }
    }
    return true;
}

bool App::MenuContributeur()
{
    // const std::vector<std::string> menuVosDonnees = {"Votre score global", "Liste de vos données"};
    return true;
}

bool App::MenuAnalyste()
{
    // const std::vector<std::string> menuAnalyse = {"Filtrage…", "Statistiques…"};
    // const std::vector<std::string> menuAnalyseFiltrage = {"Définir une région d'analyse"};
    // const std::vector<std::string> menuAnalyseStats = {"Choisir séries"};
    // const std::vector<std::string> menuAnalyseStatsCalculsSolo = {"Moyenne", "Médian", "Écart-type"};
    // const std::vector<std::string> menuAnalyseStatsCalculsMulti = {"Corrélation"};
    return true;
}

bool App::MenuExpert()
{
    // const std::vector<std::string> menuSources = {"Liste des sources", "Qualité des données", "Données médiocres"};
    return true;
}

bool App::MenuAdmin()
{
    // const std::vector<std::string> menuAdministration = {"Supprimer un utilisateur", "Modifier un utilisateur", "Réinit. un mot de passe"};
    return true;
}

bool App::MenuSuperAdmin()
{
    return this->MenuAdmin();
}

// fonctions utilitaires
// lire un entier
App::ReadIntegerResult
App::readInteger(std::istream &in)
{
    std::string input;
    std::getline(in, input);

    ReadIntegerResult res;

    try
    {
        const int value = std::stoi(input);
        res.value = value;
        res.valid = true;
    }
    catch (std::invalid_argument)
    {
        res.value = 0;
        res.valid = false;
    }

    return res;
}

// centrer une chaine de caractères
std::string
App::util_stringCenter(std::string const &str, int targetSize)
{
    int padding = targetSize - str.length();
    if (padding > 0)
    {
        int half = padding / 2;
        return std::string(half, ' ') + str + std::string(padding - half, ' ');
    }
    return str;
}

void App::banner(std::string text, bool thick, std::ostream &out)
{
    const int width = maxWidth;

    if (thick)
        out << primaryBg << primaryFg << std::string(width, ' ') << ANSI_FG_RESET << ANSI_BG_RESET << std::endl;
    out << primaryBg << primaryFg << util_stringCenter(text, width) << ANSI_FG_RESET << ANSI_BG_RESET << std::endl;

    if (thick)
        out << primaryBg << primaryFg << std::string(width, ' ') << ANSI_FG_RESET << ANSI_BG_RESET << std::endl;
}

/**
 * Attention :
 * - renvoie un entier entre 0 et (N - 1) lorsque le choix est valide
 * - renvoie App::InvalidMenuChoice sinon
 */
int App::menu(const std::string menuName, const std::vector<std::string> &entries, std::ostream &out)
{
    banner(menuName, false, out);
    out << std::endl;

    int i = 0;
    for (auto const &entry : entries)
    {
        i += 1;
        out << ANSI_FG_BLUE << std::setw(4) << i << ". " << ANSI_FG_RESET << ANSI_BOLD_ON << entry << ANSI_BOLD_OFF << std::endl;
    }
    const int n = i;

    out << std::endl;
    out << "Entrez ici votre sélection : " << ANSI_FG_BLUE;

    auto res = readInteger();
    out << ANSI_FG_RESET;
    out << std::endl;

    if (!res.valid || res.value < 1 || res.value > n)
    {
        out << ANSI_FG_RED << "Entrée invalide, veuillez entrer un entier entre " << 1 << " et " << n << "." << ANSI_FG_RESET << std::endl;
        return InvalidMenuChoice;
    }
    else
    {
        return res.value - 1;
    }
}

void App::userbar(std::string username, std::ostream &out)
{
    const int width = maxWidth;

    const std::string preamble = "   Utilisateur: ";
    int space = width - username.length() - preamble.length();
    if (space < 0)
    {
        space = 0;
    }

    out << secondaryBg << primaryFg << preamble << username << std::string(space, ' ') << ANSI_FG_RESET << ANSI_BG_RESET << std::endl;
}

App::App()
{
}
App::~App()
{
}