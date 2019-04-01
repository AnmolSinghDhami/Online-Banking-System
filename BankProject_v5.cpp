#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
using namespace std;
SYSTEMTIME stime;
class bank
{
private:
    float bal[50],amount[50];
    string ifsc[50],pass[50],id[50],fname[50],lname[50],title[50],from[50],to[50],date[50];
    int tr_id[50];
    int tran_id;
public:
    string tempid,send_acc,rsend_acc,send_ifsc,find_ifsc;
    int i,siz,current,pass_flag,choice,num_trans,transiz,trans_cur,transaction_choice;
    float send_amount;
    char ch,yes_no,anykey;
    bank()
    {
    	pass_flag=0;
    	num_trans=0;
    	ifstream transac;
		transac.open("transaction.txt");
		i=0;
		while(!transac.eof())												//transaction log
		{
			transac>>from[i];
			transac>>to[i];
			transac>>amount[i];
			transac>>date[i];
			transac>>tr_id[i];
			i++;
		}
		transac.close();
		transiz=i;
		tran_id=tr_id[transiz-1]+1;
		ifstream basicinfo;													//basic information
        basicinfo.open("basic.txt");
        i=0;
        while(!basicinfo.eof())
		{
            basicinfo>>id[i];
            basicinfo>>pass[i];
            basicinfo>>title[i];
			basicinfo>>fname[i];
            basicinfo>>lname[i];
            basicinfo>>ifsc[i];
            i++;
        }
        siz=i;
        basicinfo.close();
        ifstream balance;
        balance.open("balance.txt",ios::in);								//balance info
        i=0;
        while(!balance.eof())
        {
        	balance>>bal[i];
        	i++;
		}
	}
    void login()
    {
        acc:cout<<"Enter Account Number\t\t";
        cin>>tempid;
        for(i=0;i<siz;i++)
        {
            if(tempid.compare(id[i])==0)
            {
                pass:cout<<"Enter Password\t\t\t";
                string temppass="";
                ch=_getch();
                while(ch!=13)
                {
                	temppass.push_back(ch);
                	cout<<"*";
                	ch=_getch();
				}
                if(temppass.compare(pass[i])==0)
                {
                    current=i;
                    break;
                }
                else
                {
                	system("cls");
					cout<<"INVALID PASSWORD"<<endl<<endl;
                	pass_flag++;
                	if(pass_flag>3)
                	{
                		cout<<"TOO MANY FAILED ATEMPTS"<<endl;
                		exit(0);
					}
					else
						goto pass;
				}
            }
        }
        if(i==siz)
        {
        	system("cls");
			cout<<"INVALID ACCOUNT NUMBER"<<endl<<endl;
        	goto acc;
		}
    }
    void home_details()
    {
    	system("cls");
    	cout<<"\t\t\t\t\t\tSTATE BANK OF INDIA"<<endl;
    	cout<<"Account Number:\t"<<id[current]<<endl;
    	cout<<"IFSC Code:\t"<<ifsc[current]<<endl;
    	cout<<"Availabe Bal:\t"<<bal[current]<<endl;
    	cout<<title[current]<<" "<<fname[current]<<" "<<lname[current]<<" "<<endl<<endl<<endl;
   	}
   	void menu()
   	{
		cout<<"Transaction Log\t\t\t\t1"<<endl;
    	cout<<"Money Transfer\t\t\t\t2"<<endl;
    	cout<<"Bill payment\t\t\t\t3"<<endl;
    	cout<<"Mobile Recharge\t\t\t\t4"<<endl;
    	cout<<"Logout\t\t\t\t\t5"<<endl;
    	cout<<"Exit\t\t\t\t\t6"<<endl;
    	cin>>choice;
    	switch(choice)
		{
			case 1:{
				system("cls");
				home_details();
				ifstream transac;
				transac.open("transaction.txt",ios::in);
				i=0;
				while(!transac.eof())												//transaction log
				{
					transac>>from[i];
					transac>>to[i];
					transac>>amount[i];
					transac>>date[i];
					transac>>tr_id[i];
					i++;
				}
				transiz=i;
				transac.close();
				transaction:cout<<"Last 5 transactions\t\t\t1"<<endl<<"All transactions\t\t\t2"<<endl;
				int transaction_flag=0;
				cin>>transaction_choice;
				switch(transaction_choice)
				{
					case 1:{
						system("cls");
						home_details();
						cout<<"Transaction ID\t\tSender\t\t\tDate\t\t\tReciver\t\t\tAmount"<<endl<<endl;
						for(i=transiz-1;i>=0;i--)
						{
							if(id[current].compare(from[i])==0 || id[current].compare(to[i])==0)
							{
								cout<<tr_id[i]<<"\t\t"<<from[i]<<"\t\t"<<date[i]<<"\t\t"<<to[i]<<"\t\t"<<amount[i]<<endl;
								transaction_flag++;
							}
							if(transaction_flag==5)
							{
								break;
								cout<<endl;
							}
						}
						cout<<endl;
						cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
					}
					case 2:{
						system("cls");
						home_details();
						cout<<"Transaction ID\t\tSender\t\t\tDate\t\t\tReciver\t\t\tAmount"<<endl<<endl;
						for(i=transiz-1;i>=0;i--)
						{
							if(id[current].compare(from[i])==0 || id[current].compare(to[i])==0)
							{
								cout<<tr_id[i]<<"\t\t"<<from[i]<<"\t\t"<<date[i]<<"\t\t"<<to[i]<<"\t\t"<<amount[i]<<endl;
							}
						}
						cout<<endl;
						cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
					}
					default:{
						cout<<"INVALID INPUT!"<<endl<<endl;
						goto transaction;
						break;
					}
				}
				break;
			}
			case 2:{
				system("cls");
				home_details();
				transaction_start:cout<<"Enter account number\t\t";
				cin>>send_acc;
				cout<<"Re-enter account number\t\t";
				cin>>rsend_acc;
				if(send_acc.compare(rsend_acc)==0)
				{
				    if(send_acc.compare(id[current])==0)
                    {
                        cout<<endl<<endl<<"Please do not enter your own account number"<<endl<<endl;
                        goto transaction_start;
                    }
					cout<<"Enter IFSC code\t\t\t";
					cin>>send_ifsc;
					for(i=0;i<siz;i++)
					{
						if(send_acc.compare(id[i])==0)
						{
							find_ifsc=ifsc[i];
							break;
						}
					}
					trans_cur=i;
					if(send_ifsc.compare(find_ifsc)==0 && send_acc.compare(id[trans_cur])==0)
					{
						cout<<"Enter Amount\t\t\tRs";
						cin>>send_amount;
						cout<<endl<<"Do you wish to proceed? ('Y' for yes)"<<endl;
						cin>>yes_no;

                        if(yes_no=='y' || yes_no=='Y')
                        {
                            if((bal[current]-send_amount)<0)
							{
								cout<<endl<<"INSUFFICIENT BALANCE"<<endl<<endl;
								cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
							}
							else
							{
								bal[current]=bal[current]-send_amount;
								bal[trans_cur]=bal[trans_cur]+send_amount;
								cout<<endl<<"Transfer Succesfull"<<endl<<"Transaction ID-"<<tran_id<<endl<<endl;
								ofstream send_trans;
								send_trans.open("transaction.txt",ios::app);
								send_trans<<"\n"<<id[current]<<"\n";
								send_trans<<send_acc<<"\n";
								send_trans<<send_amount<<"\n";
								send_trans<<stime.wDay<<"/"<<stime.wMonth<<"/"<<stime.wYear<<"\n";
								send_trans<<tran_id;

								send_trans.close();
								ofstream send_basic;
								send_basic.open("balance.txt",ios::trunc);
								for(i=0;i<3;i++)
								{
    	        					send_basic<<bal[i]<<endl;
								}
								send_basic.close();
								tran_id++;
							}
                        }
                        else
                        {
                            system("cls");
                            home_details();
                            break;
                        }
					}
							else
							{
								cout<<endl<<"Entered details are wrong!!"<<endl<<endl;
								goto transaction_start;
							}

					}
					else
                    {
                        cout<<endl<<"Make sure the entered account number is correct"<<endl<<endl;
                        goto transaction_start;
                    }

                cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
		}
			case 3:{
				system("cls");
				home_details();
				string companies[4]={"0","Connect_Broad","NetPlus_Broad","Lovely_Pro_Uni"};
				int choice_comp;
				float amm_comp;
				cout<<"Connect Broadband\t\t\t\t1"<<endl<<"NetPlus Broadband\t\t\t\t2"<<endl<<"Lovely Professional University\t\t\t3"<<endl;
				cin>>choice_comp;
				cout<<"Enter amount\t";
				cin>>amm_comp;
				cout<<endl<<"Do you wish to proceed? ('Y' for yes)"<<endl;
				cin>>yes_no;
            if(yes_no=='y' || yes_no=='Y')
            {
                if(bal[current]-amm_comp<0)
                {
                    cout<<endl<<endl<<"INSUFFICIENT BALANCE"<<endl<<endl;
                    cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
                }
                else{
				bal[current]=bal[current]-amm_comp;
				cout<<endl<<"Transfer Succesfull"<<endl<<"Transaction ID-"<<tran_id<<endl<<endl;
				ofstream send_comp;
				send_comp.open("transaction.txt",ios::app);

				send_comp<<"\n"<<id[current]<<"\n";
				send_comp<<companies[choice_comp]<<"\n";
				send_comp<<amm_comp<<"\n";
				send_comp<<stime.wDay<<"/"<<stime.wMonth<<"/"<<stime.wYear<<"\n";
				send_comp<<tran_id;

				send_comp.close();
				ofstream send_basic_comp;
				send_basic_comp.open("balance.txt",ios::trunc);
				for(i=0;i<3;i++)
				{
            		send_basic_comp<<bal[i]<<endl;
				}
				send_basic_comp.close();
				tran_id++;
				cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
                }
            }
            else
            {
                system("cls");
                home_details();
                break;
            }
			}
			case 4:{
				system("cls");
				home_details();
				string mobile_companies[4]={"0","Airtel_Tele","Jio_Telecom","Idea_Telecom"};
				int choice_mob;
				float amm_mob;
				cout<<"Airtel\t\t\t\t1"<<endl<<"Jio\t\t\t\t2"<<endl<<"Idea\t\t\t\t3"<<endl;
				cin>>choice_mob;
				cout<<"Enter amount\t";
				cin>>amm_mob;
				cout<<endl<<"Do you wish to proceed? ('Y' for yes)"<<endl;
				cin>>yes_no;
            if(yes_no=='y' || yes_no=='Y')
            {
				if((bal[current]-amm_mob)>0)
                {
				bal[current]=bal[current]-amm_mob;
				cout<<endl<<"Transfer Succesfull"<<endl<<"Transaction ID-"<<tran_id<<endl<<endl;
				ofstream send_mob;
				send_mob.open("transaction.txt",ios::app);

				send_mob<<"\n"<<id[current]<<"\n";
				send_mob<<mobile_companies[choice_mob]<<"\n";
				send_mob<<amm_mob<<"\n";
				send_mob<<stime.wDay<<"/"<<stime.wMonth<<"/"<<stime.wYear<<"\n";
				send_mob<<tran_id;

				send_mob.close();
				ofstream send_basic_mob;
				send_basic_mob.open("balance.txt",ios::trunc);
				for(i=0;i<3;i++)
				{
            		send_basic_mob<<bal[i]<<endl;
				}
				send_basic_mob.close();
				tran_id++;
				cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
                }
                else
                {
                    cout<<endl<<"INSUFFICIENT BALANCE"<<endl<<endl;
                    cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
                }
            }
            else
            {
                system("cls");
                home_details();
                break;
            }
			}
			case 5:{
				system("cls");
				login();
				system("cls");
				home_details();
				break;
			}
			case 6:{
				exit(0);
				break;
			}
			default:{
				cout<<endl<<"INVALID INPUT!"<<endl<<endl;
				cout<<"Press any key to continue....";
						anykey=_getch();
						if(anykey)
                        {
                                break;
                        }
			}
		}
	}

};
int main()
{
	GetSystemTime(&stime);
	bank data;
	data.login();
	data.home_details();
	while(1)
	{
		system("cls");
		data.home_details();
		data.menu();
	}
	return 0;
}
