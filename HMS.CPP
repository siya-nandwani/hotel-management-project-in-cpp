#include<iostream>
#include<fstream>
using namespace std;

class ROOMS{
    public:
    int roomNo;
    string type; //deluxe,ac,no-ac
    float price; //deluxe->2000/day....ac->1500/day....non ac->1000/day
    int availablity;//1 for available , 0 for not available

    void inputR(){
        cout<<"ENTER ROOM NO: "<<endl;
        cin>>roomNo;
        cout<<"ENTER type of room: "<<endl;
        cin>>type;
        cout<<"ENTER price of room: "<<endl;
        cin>>price;
        cout<<"ENTER AVAILABLITY: "<<endl;
        cin>>availablity;
    }

    void displayR(){
        cout<<"---DETAILS OF ROOM NO."<<roomNo<<"are-----"<<endl;
        cout<<"Type of room:"<<type<<endl;
        cout<<"Price:"<<price<<endl;
        cout<<"Availablity:"<<availablity<<endl;
    }
    
    void addR(){
        ROOMS r;
        r.inputR();
        fstream fobj;
        fobj.open("Rooms.dat",ios::app|ios::binary);
        if(!fobj){
            cout<<"FILE NOT FOUND"<<endl;
            return;
        }
        fobj.write((char*)&r,sizeof(r));
        fobj.close();
    }

    void viewR(){
        int rN;
        cout<<"Enter room no. to be viewed:"<<endl;
        cin>>rN;
        fstream fobj;
        fobj.open("Rooms.dat",ios::in|ios::binary);
        if(!fobj){
            cout<<"FILE NOT FOUND"<<endl;
            return;
        }
        ROOMS r;
        while(fobj.read((char*)&r,sizeof(r))){
            if(r.roomNo==rN){
                r.displayR();
            }else{
                cout<<"ROOM NOT FOUND"<<endl;
            }

        }
        fobj.close();
    }

};

class CUSTOMER:public ROOMS{
    public:
    string name;
    int age;
    string ID;
    string phn;//phone no.
    int adp;//advance payment
    string date; //format->"yyyy/mm/dd"
    string time;
    int no_of_days; //format->"//hh:mm"
    float totalAmt;
    void inputC(){
        cout<<"Enter name of customer:"<<endl;
        cin>>name;
        cout<<"Enter age:"<<endl;
        cin>>age;
        cout<<"Enter ID:"<<endl;
        cin>>ID;
        cout<<"Enter phone number:"<<endl;
        cin>>phn;
        cout<<"Enter no. of days:"<<endl;
        cin>>no_of_days;
        cout<<"DO ADVANCE PAYMENT OF RS.500 DONE?"<<endl;//ENTER 1 FOR YES AND 0 FOR NO
        cin>>adp;
    }

    void displayC(){
        cout<<"-----DETAILS FOR CUSTOMER NAME-"<<name<<"are------";
        cout<<"AGE: "<<age<<endl;
        cout<<"ID: "<<ID<<endl;
        cout<<"PHONE NUMBER:"<<phn<<endl;
        cout<<"ADVANCE PAYMENT:"<<adp<<endl;
        cout<<"ROOM NO. BOOKED:"<<roomNo<<endl;
        cout<<"TYPE OF ROOM:"<<type<<endl;
        cout<<"PRICE:"<<price<<endl;
    }

    void addC(){
        fstream fobj;
        fobj.open("Customer.dat",ios::out|ios::binary);
        if(!fobj){
            cout<<"FILE NOT FOUND"<<endl;
            return;
        }
        CUSTOMER c;
        c.inputC();
        c.checkIN();
        fobj.write((char*)&c,sizeof(c));
        fobj.close();
    }

    void viewC(){
        string nC;
        cout<<"ENTER NAME OF CUSTOMER TO BE SEARCHED:";
        cin>>nC;
        fstream fobj;
        fobj.open("Customer.dat",ios::in|ios::binary);
        if(!fobj){
            cout<<"FILE NOT FOUND"<<endl;
            return;
        }

        CUSTOMER c;
        while(fobj.read((char*)&c,sizeof(c))){
            if(c.name==nC){
                c.displayC();
            }else{
                cout<<"CUSTOMER RECORD NOT FOUND";
            }
        }
        fobj.close();
    }

    void checkIN(){
        cout<<"ENTER CHECK-IN TIME:"<<endl;
        cin>>time;
        cout<<"ENTER DATE OF CHECK-IN:"<<endl;
        cin>>date;
    } 

    void checkOUT(){
        cout<<"ENTER CHECK-IN TIME:"<<endl;
        cin>>time;
        cout<<"ENTER DATE OF CHECK-IN:"<<endl;
        cin>>date;
    }

    void generateBill(){
        if(adp==1){
            totalAmt= (CUSTOMER::price)*no_of_days -500;
            cout<<"total amount: "<<totalAmt;
        }else{
            totalAmt=(CUSTOMER::price)*no_of_days ;
            cout<<"total amount: "<<totalAmt;
        }
    }

};

class HOTEL:public CUSTOMER{
    public:
    void bookR(){
        string desiredType;
        cout<<"ENTER TYPE OF ROOM: "<<endl;
        cin>>desiredType;
        fstream fobj;
        fobj.open("Rooms.dat",ios::in|ios::binary|ios::out);
        if(!fobj){
            cout<<"FILE NOT FOUND"<<endl;
            return;
        }
        ROOMS r;
        CUSTOMER c;
        while(fobj.read((char*)&r,sizeof(r))){
            if(r.type==desiredType){
                if(r.availablity==1){
                    cout<<"YES THE ROOM IS AVAILABLE!!!!"<<endl;
                    c.addC();
                    r.availablity=0;
                    int pos = fobj.tellg();                   // current read position
                    fobj.seekp(pos - sizeof(r));             // move back to the start of that object
                    fobj.write((char*)&r, sizeof(r));        // overwrite with updated availability

                }else{
                    cout<<"SORRY,ROOM NOT AVAILABLE!!"<<endl;
                }
            }
        }

        fobj.close();
    }

    void exit(){
        fstream fobj;
        fobj.open("Customer.dat",ios::in|ios::binary);
        if(!fobj){
            cout<<"FILE NOT FOUND"<<endl;
            return;
        }
        CUSTOMER c;
        c.checkOUT();
        c.generateBill();
        fobj.write((char*)&c,sizeof(c));
        fobj.close();
    }
};

int main(){
    cout<<"!!!!!!!!WELCOME!!!!!!!!!!!"<<endl;
    HOTEL h;
    int n;
    cout<<"ENTER YOUR CHOICE: 0 for adding a room, 1 for BOOK A ROOM ,2 for VIEW ANY ROOM ,3 for VIEW CUSTOMER DETAILS , 4 for exit and bill generation ";
    cin>>n;
    switch(n){
        case 0:
        h.addR();
        break; 
        
        case 1:
        h.bookR();
        break;

        case 2:
        h.CUSTOMER::viewR();
        break;

        case 3:
        h.viewC();
        break;

        case 4:
        h.exit();
        break;
   
    }

    cout<<"------THANKYOUU------"<<endl;
    return 0;
}