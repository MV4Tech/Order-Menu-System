#include <iostream>
#include <AuthService.h>
#include <MenuService.h>
#include <conio.h>
#include <random>
#include "tabulate.hpp"


std::string username;
int id;

void menuStudent(int role, std::string addedBy, int id) {
    MenuService ms;
    AuthService as;



    int maxMenus;
    int exitChangeMenu = 0;
    double sumOfMenus = 0;
    int votedChanged;
    int alreadyReserved = 0;
    maxMenus = ms.numberOfMenus();
    if (as.statusOfReservation(id) != 1) {

    
        while (true) {
         // STUDENT PART of the school/uni
            if (exitChangeMenu == 1) {
                break;
            }
            int menuIDVoted;
            std::cout << "\nACCOUNT STATUS: STUDENT\n";
            std::cout << "\n\n----MENU----\n\n";
            int choice = 0;
            std::cout << "Hello " << addedBy << " Choose what u want to do." << std::endl;
            std::cout << "1.Menu Reservation." << std::endl;
            std::cout << "2.Information." << std::endl;
            std::cout << "3.Exit." << std::endl;
            std::cout << "\n";
            std::cin >> choice;
            std::cin.clear();
            if (choice == 1) {
                std::cout << "------------------------------MENU RESERVATIONA------------------------------\n";
                
                ms.showMenu();
                std::cout << "\n";

                bool flag = true;
                while (flag) {
                    //departments number
                    std::cout << "Specify the ID of the menu you want to eat: ";
                    std::cin >> menuIDVoted;
                    if (std::cin.fail())
                    {

                        std::cin.clear(); // removes cin error flag
                        std::cin.ignore(INT_MAX, '\n');  // ignore last input
                        std::cout << "You have to input a number!\n";
                        //system("CLS");
                    }                    
                    else if (menuIDVoted > maxMenus || menuIDVoted < 0) {
                        std::cout << "\nPlease select between 1 - " << maxMenus << ".\n";
                    }
                    else
                    
                    {

                        flag = false;
                    }

                }


                votedChanged = menuIDVoted;
                ms.changeVotePole(menuIDVoted);
                as.updateMenu(id,ms.printMenu(menuIDVoted));

                    system("CLS");
                    sumOfMenus = 4.20;
            
                    char ch1 = '+';
                    std::cout << "------------------------------INFORMATION----------------------------";
                    std::cout << "\nStudent username: " + addedBy << "\nStudent ID: " << id << "\nBill: " << sumOfMenus << " LEV" << "\n* Statut of dicount: " << ch1 << "\n\n";
                    std::cout << "Your choice is: ";
                    std::cout<< ms.printMenu(menuIDVoted); 
                    std::cout << "\n\nYou can reserve only one menu per day!\n";
                    std::cout << "\n\nPress enter to continue!\n";
                    as.reservationStatus(id);
                   
                    _getch();

                    int choice2;
                    while (true) {
                        system("CLS");
                    std::cout << "\n1.Change Menu." << std::endl;
                    std::cout << "2.Information." << std::endl;
                    std::cout << "3.Bill - " << sumOfMenus << "LEV" << std::endl;
                    std::cout << "4.Exit(Restart For Changing). " << std::endl;
                    std::cin >> choice2;
                        if (choice2 == 1) {
                            int i=0;
                            int v;
                       
                            std::cout << "------------------------------MENU RESERVATION------------------------------\n";
                          
                            ms.showMenu();
                            std::cout << "\n";
                            std::cout << "\n";
                            bool flag = true;
                            while (flag) {
                                //departments number
                                std::cout << "Specify the ID of the menu you want to eat: ";
                                std::cin >> v;
                                if (std::cin.fail())
                                {

                                    std::cin.clear(); // removes cin error flag
                                    std::cin.ignore(INT_MAX, '\n');  // ignore last input
                                    std::cout << "You have to input a number!\n";
                                    //system("CLS");
                                } else if (v > maxMenus || v < 0) {
                                    std::cout << "\nPlease select between 1 - " << maxMenus << ".\n";
                                }
                                else
                                {

                                    flag = false;
                                }

                            }

                            ms.changeVotePole(v);
                            ms.minusOneVote(votedChanged);
                            as.updateMenu(id, ms.printMenu(v));
                            as.reservationStatus(id);
                        }
                        else if (choice2 == 2) {
                            system("CLS");
                            std::cout << "------------------------------INFORMATION------------------------------\n\n";
                            std::cout << "Student username: " + addedBy << "\nStudent ID: " << id << "\nStatut of dicount: " << '+' << "\n\nMenu will cost 4.20 LEVA!\n";
                            std::cout << "Your choice is: ";
                            std::cout << as.printMenu(id);
                            std::cout << "\nPress enter to continue.";
                            _getch();

                        }
                        else if (choice2 == 4) {
                            exitChangeMenu = 1;
                            break;
                            //exit(0);
                        }
                        else {
                            std::cout << "Please select between a number.";
                            _getch();
                            std::cin.clear(); // removes cin error flag
                            std::cin.ignore(INT_MAX, '\n');
                            system("CLS");
                        }
                    }
            }
            else if (choice == 2) {
                system("CLS");
                
                
                    std::cout << "------------------------------INFORMATION------------------------------\n\n";
                    std::cout << "Student username: " + addedBy << "\nStudent ID: " << id << "\nStatut of dicount: " << '+' << "\n\nMenu will cost 4.20 LEVA!\n";
                    std::cout << "Your choice is: ";
                    std::cout << as.printMenu(id);
                    
                
          
            }
            else if (choice == 3) {
                break;
            }
            else {
                std::cout << "Please select number between 1 - 4";
                _getch();
                std::cin.clear(); // removes cin error flag
                std::cin.ignore(INT_MAX, '\n');
                system("CLS");
            }

        
        }
    }
    else {
        std::cout << "------------------------------INFORMATION------------------------------\n\n";
        std::cout << "Student username: " + addedBy << "\nStudent ID: " << id << "\nStatut of dicount: " << '+' << "\nMenu will cost 4.20 LEVA!\n";
        std::cout << "Your choice is: ";
        std::cout << as.printMenu(id);
        std::cout << "\n\nPress enter to exit.";
            _getch();
    }
}

void menuAdmin(int role, std::string addedBy) {
    MenuService ms;
    AuthService as;
    int maxMenus;
    //maxMenus = ms.numberOfMenus();
    while (true) {
        if (role == 2) {
            std::cout << "\nACCOUNT STATUS: ADMIN\n";
            std::cout << "\n\n----MENU----\n\n";
            int choice = 0;
            std::cout << "Hello " << addedBy << " Choose what u want to do." << std::endl;
            std::cout << "1.Add Menu." << std::endl;
            std::cout << "2.Remove Menu." << std::endl;
            std::cout << "3.Show All Menus." << std::endl;
            std::cout << "4.Show Users Info." << std::endl;
            std::cout << "5.Exit." << std::endl;

            std::cin >> choice;
            std::cin.clear();
            if (choice == 1) {
                std::cout << "------------------------------ADD MENU------------------------------\n";
                std::string menu;
                std::cout << "Enter menu : ";
                std::cin.ignore();
                std::getline(std::cin, menu);


                ms.addMenu(menu, addedBy);
                system("CLS");
                choice = 0;
            }
            else if (choice == 2) {
                system("CLS");
                int removedMenuID;
                std::cout << "------------------------------REMOVE MENU------------------------------\n";
                std::cout << "--All menus--\n\n";
                std::cout << "MENU /Added By /Votes / ID\n";

                ms.showMenu();
                std::cout << "\n";


                maxMenus = ms.numberOfMenus();
                bool flag = true;
                while (flag) {
                    //departments number
                    std::cout << "Specify the ID of the menu you want to eat: ";
                    std::cin >> removedMenuID;
                    if (std::cin.fail())
                    {

                        std::cin.clear(); // removes cin error flag
                        std::cin.ignore(INT_MAX, '\n');  // ignore last input
                        std::cout << "You have to input a number!\n";
                        //system("CLS");
                    }
                    else if (removedMenuID > maxMenus || removedMenuID < 0) {
                        std::cout << "\nPlease select between 1 - " << maxMenus << ".\n";
                    }

                    else
                    {

                        flag = false;
                    }

                }


                ms.removeMenu(removedMenuID);
                std::cout << "\n";
                std::cout << "\n";
                std::cout << "--Updated List--\n\n";

                ms.showMenu();
            }
            else if (choice == 3) {
                system("CLS");
                std::cout << "------------------------------ALL MENUS------------------------------\n\n";
                std::cout << "\n";
               
                ms.showMenu();
                std::cout << "\n"; 

            }
            else if (choice == 4) {
                system("CLS");
                as.printAllStudents();
            }
            else if(choice == 5){
                break;
            }
            else {
                std::cout << "Please select between 1, 2, 3 or 4";
                _getch();
                std::cin.clear(); // removes cin error flag
                std::cin.ignore(INT_MAX, '\n');
            }
        }        

    }
}

void menuGuest(std::string addedBy) {
    system("CLS");
    MenuService ms;
    AuthService as;
    int maxMenus;

    while (true) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(100000, 1000000); // define the range

  


        std::cout << "------------------------------INFORMATION------------------------------\n\n";
        std::cout << "\nSTATUS: Guest\n";
        std::cout << "\nStatut of dicount: " << '-' << "\nMenu will cost 7.20 LEVA!\n\n";
        std::cout << "--All menus--\n\n";
        //menuInfo.add_row({ "Menu","Added By", "Votes", "Menu ID" });
        ms.showMenu();
        int choice;


        //std::cout << "\nPlease select menu: ";
        //std::cin >> choice;
        maxMenus = ms.numberOfMenus();
        bool flag = true;
        while (flag) {
            //departments number
            std::cout << "\nPlease select menu: ";
            std::cin >> choice;
            if (std::cin.fail())
            {

                std::cin.clear(); // removes cin error flag
                std::cin.ignore(INT_MAX, '\n');  // ignore last input
                std::cout << "You have to input a number!\n";
                //system("CLS");
            }
            else if (choice > maxMenus || choice < 0) {
                std::cout << "\nPlease select between 1 - " << maxMenus << ".\n";
            }
            else
            {

                flag = false;
            }

        }

        std::cout << "\nYour choice is: ";
        std::cout<< ms.printMenu(choice);
        std::cout << "\nYour reservation id is: ";
        std::cout << distr(gen);
        ms.changeVotePole(choice); 
        std::cout << "\nPlease press enter to finish your reservetion.";
        _getch();
        break;
    }



}

void menuCooker(std::string username) {
    MenuService ms;
    AuthService as;
    int maxMenus;

    while (true) {
        int choice = 0;
        std::cout << "\nACCOUNT STATUS: Cooker\n";
        std::cout << "\nHello " << username << " Choose what u want to do." << std::endl;
        std::cout << "1.Show Menus." << std::endl;
        std::cout << "2.Restart Students Reservation." << std::endl;
        std::cout << "3.Add Menus." << std::endl;
        std::cout << "4.Remove menus." << std::endl;
        std::cout << "5.Exit." << std::endl;
        std::cin >> choice;
        if (choice == 1) {
            // show menus
            //menuInfo.add_row({ "Menu","Added By", "Votes", "Menu ID" });
            ms.showMenu();
        }
        else if (choice == 2) {
            // clear menus
        
            as.setReservationStatusToZero();

            std::cout << "\nStudent reservation rest.\n";
        }
        else if (choice == 3) {
            // add menus
            std::cout << "------------------------------ADD MENU------------------------------\n";
            std::string menu;
            std::cout << "Enter menu : ";
            std::cin.ignore();
            std::getline(std::cin, menu);
            ms.addMenu(menu, username);
            system("CLS");
            choice = 0;

        }
        else if (choice == 4) {
            // Remove menus
            system("CLS");
            int removedMenuID;
            std::cout << "------------------------------REMOVE MENU------------------------------\n";
            std::cout << "--All menus--\n\n";
            //menuInfo.add_row({ "Menu","Added By", "Votes", "Menu ID" });
            ms.showMenu();
            std::cout << "\n";

            maxMenus = ms.numberOfMenus();
            bool flag = true;
            while (flag) {
                //departments number
                std::cout << "Specify the ID of the menu you want to remove: ";
                std::cin >> removedMenuID;
                if (std::cin.fail())
                {

                    std::cin.clear(); // removes cin error flag
                    std::cin.ignore(INT_MAX, '\n');  // ignore last input
                    std::cout << "You have to input a number!\n";
                    //system("CLS");
                }
                else if (removedMenuID > maxMenus || removedMenuID < 0) {
                    std::cout << "\nPlease select between 1 - " << maxMenus << ".\n";
                }
                else
                {

                    flag = false;
                }

            }


            ms.removeMenu(removedMenuID);
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "--Updated List--\n\n";
            ms.showMenu();

        }
        else if (choice == 5) {
            break;
        }
        else {
            std::cout << "\nPlease select between 1 - 5";
            _getch();
            std::cin.clear(); // removes cin error flag
            std::cin.ignore(INT_MAX, '\n');

        }

        
    }

}


int main()
{
    
    AuthService authService;
 
    while (true)
    {
        //bad (remove this)
        system("CLS");

        std::cout << "Select a option: 1. Login, 2. Register, 3. Reserve as guest" << std::endl;

        int option;
        //try {
        std::cin >> option;
 
        if (option == 1)
        {
            //bad (remove this)
            system("CLS");
           

            std::string username;
            std::string password;
          
            std::cout << "Enter Your username: ";
            std::cin >> username;
            std::cout << "Enter Your password: ";
            std::cin >> password;
            int id;
            int pickedRole;
            try
            {
                auto res = authService.login(username, password);
                username = res.username;
                pickedRole = res.role;
                id = res.id;
                std::cout << "My id is " << res.id <<  "\n";
                std::cout << "My name is " << username << "\n";
                std::cout << "My role is " << pickedRole << "\n";
                std::cout << "------------------------------------------------\n";
                system("CLS");
                if (res.role == 2) {
                    menuAdmin(pickedRole, username);
                }
                else if (res.role == 1) {
                menuStudent(pickedRole,username,res.id);

                }
                else if (res.role == 3) {
                    menuCooker(res.username);
                }
                

            }
            catch (std::string ex)
            {
                std::cout << "There was a problem: " << ex;
                _getch();
            }

            
        }
        else if (option == 2)
        {
            //bad (remove this)
            system("CLS");

            //bad (remove this)
            system("CLS");

            std::string username;
            std::string password;
            
            int pickRole;
            std::cout << "Enter Your username: ";
            std::cin >> username;
            std::cout << "Enter Your password: ";
            std::cin >> password;
            std::cout << "\nFor student role enter: 1\n";
            std::cout << "Enter Your role: ";
            std::cin >> pickRole;


            try
            {
                authService.createAccount(username, password,pickRole);

                std::cout << "Account created succesfully";
            }
            catch (std::string ex)
            {
                std::cout << "There was a problem: " << ex;
            }

            _getch();
        }
        else if (option == 3) {
            Response r;
            menuGuest(r.username);

        }
        else {
            std::cout << "Please select between 1, 2 or 3";
            _getch();
            std::cin.clear(); // removes cin error flag
            std::cin.ignore(INT_MAX, '\n');
        }
    }
    return 0;
   
}


