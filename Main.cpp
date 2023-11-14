#include <iostream>
    using namespace std;

    class product
        {
            public :
            const int MAX_STOCK = 10;

            string *name = new string;
            int *price = new int,
                *remaining_stock = new int;

            product(string n, int p)
                {
                    *price = p;
                    *name = *name + n;
                    *remaining_stock = MAX_STOCK;
                }
            ~product()
                {
                    delete price;
                    delete name;
                    delete remaining_stock;
                }
        };
        class money
        {
            public :

            int *max = new int;
            int *accepted_values = new int[10];
            int i;
            money()
                {
                }
            money(int *a, int how_many)
                {
                    *max = how_many;
                    //cout<<"\n this is max now : "<<*max;
                        for (i=0; i<how_many; i++)
                            {
                                *(accepted_values + i) = a[i];
                                //cout<<"\n inside money : "<<i<<" accepted value is "<<*(accepted_values + i)<<" value is a is :"<<a[i]<<endl;
                            }           
                }
            int check(int value, int loop_max)
                {
                    //cout<<"\nInside money checker, the value of max is :"<<loop_max;
                    bool present = 0;
                    //cout<<"\nInside money checker, the value of present is :"<<present;
                    for(i=0; i< loop_max; i++)
                        {
                            //cout<<"\n Accepted values - "<<i<<" is : "<<*(accepted_values + i)<<" value is :"<<value;
                            if (value == *(accepted_values + i))
                            {
                                //cout<<"\n value present!";
                                present = 1;
                            }
                        }
                    if(!present)
                        {
                            //cout<<"\n not present and present is now : "<<present;
                            value = 0;
                        }
                    return value;
                }
            ~money()
                {
                    delete max;
                    delete accepted_values;
                }
        };class Vending_machine
        {
            public :

            product *candy = new product("Candy",10);
            product *snack = new product("Snack",50);
            product *nuts = new product("Nuts",90);
            product *coke = new product("Coke",25);
            product *soda = new product("Soda",45);

            int accepted_coins[5] = {1,5,10,25,50};
            int accepted_notes[2] = {1,2};

            money *coins = new money(accepted_coins, 5);
            money *notes = new money(accepted_notes, 2);

            int *amount_deposited = new int;

            Vending_machine()
                {
                    *amount_deposited = 0;
                }
            Vending_machine(bool reset)
                {   
                    if (reset == true)
                        {
                            *amount_deposited = 0;
                            //delete candy;
                            //delete snack;
                            //delete nuts;
                            //delete coke;
                            //delete soda;
                            //delete coins;
                            //delete notes;

                            product *candy = new product("Candy",10);
                            product *snack = new product("Snack",50);
                            product *nuts = new product("Nuts",90);
                            product *coke = new product("Coke",25);
                            product *soda = new product("Soda",45);
                            }
                }
            ~Vending_machine()
                {
                    delete candy;
                    delete snack;
                    delete nuts;
                    delete coke;
                    delete soda;
                    delete coins;
                    delete notes;
                    delete amount_deposited;
                }
            void get_money(int choice,int value)
                {
                    switch(choice)
                        {
                            case(1):
                                //cout<<"\nthis is the value of amount deposited before : "<<*amount_deposited;
                                *amount_deposited = coins->check(value, *coins->max);
                                //cout<<"\nthis is the value of amount deposited after : "<<*amount_deposited;
                            break;
                            case(2):
                                //cout<<"\nthis is the value of amount deposited before : "<<*amount_deposited;
                                *amount_deposited = notes->check(value, *notes->max) * 100;
                                //cout<<"\nthis is the value of amount deposited after : "<<*amount_deposited;
                            break;
                            default:
                                *amount_deposited = 0;
                        }
                }
            void compare_availability(int *remain, int *price)
                {
                    try
                    {
                        if(*remain !=0 && *amount_deposited >= *price)
                            {
                                *remain -= 1;;
                                *amount_deposited -= *price;
                                cout<<"\n Dispatched";
                                return_money('Y');
                            }
                        else if (*amount_deposited < *price)
                            {
                                throw "Amount deposited is low";
                            }
                        else if (*remain == 0)
                            {
                                throw "Stock not available";
                            }
                        else
                            {
                                throw "Unknown error";
                            }
                    }catch (const char* msg)
                        {
                            cout<<msg<<endl;
                        }
                }
            void get_selection(int selection)
                {
                    switch(selection)
                        {
                            case (1):
                                compare_availability(candy->remaining_stock, candy->price);
                            break;
                            case (2):
                                compare_availability(snack->remaining_stock, snack->price);
                            break;
                            case (3):
                                compare_availability(nuts->remaining_stock, nuts->price);
                            break;
                            case (4):
                                compare_availability(coke->remaining_stock, coke->price);
                            break;
                            case (5):
                                compare_availability(soda->remaining_stock, soda->price);
                            break;
                            default:
                                cout<<"Wrong selection !"<<endl;
                        }
                }
            void return_money(char choice)
            {
                if (*amount_deposited != 0)
                    { 
                        if (choice == 'Y' || choice == 'y')
                            {
                                cout<<"\n Your remaining change is : " << *amount_deposited/100.0 <<" $ \n";
                                *amount_deposited = 0;
                            }
                    }
            }
        };
    int main() 
        {
            int main_select, main_coin_note, main_val;
            char change_your_mind;
            Vending_machine *a = new Vending_machine(1);
            cout<<"Coin(1) or Note(2) : ";
            cin>>main_coin_note;
            cout<<"Enter your denomination :";
            cin>>main_val;
            a->get_money(main_coin_note, main_val);

            if (*a->amount_deposited == 0)
                {
                    cout<<"\n Wrong denomination, Value returned !";
                }
            else
                {
                    cout<<"\tEnter what product you want :"<<endl<<"\t\t1 for Candy"<<endl<<"\t\t2 for Snack"<<endl<<"\t\t3 for Nuts"<<endl<<"\t\t4 for Coke"<<endl<<"\t\t5 for Soda\n\t :..";
                    cin>>main_select;
                    cout<<"\n You want to cancel request?(Y/N) :";
                    cin>>change_your_mind;
                        if (change_your_mind == 'Y' || change_your_mind == 'y')
                            {
                                a->return_money(change_your_mind);
                            }
                        else
                            {
                                a->get_selection(main_select);
                            }
                }
        }
