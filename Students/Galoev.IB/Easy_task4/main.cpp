#include <iostream>
#include <vector>

using namespace std;

struct car {
    char license_plate[6];
    int color;
    int num_wheels;
    char owner[256];
};

class CaeService{
private:
    vector<car> cars;
public:
    void Registration(const car &obj){
        cars.push_back(obj);
    }
    
    void inform_by_index(int n){
        if (n<1 && n>cars.size()){
            cout<< "Invalid index"<<endl;
            return;
        }
        
        cout<<"License plate: "<<cars[n].license_plate<<endl;
        cout<<"Color: "<<cars[n].color<<endl;
        cout<<"Number wheels: "<<cars[n].num_wheels<<endl;
        cout<<"Owner: "<<cars[n].owner<<endl;
    }
    
    void inform_by_plate(const string& plate){
        if (cars.size() == 0){
            cout<<"Empty"<<endl;
            return;
        }
        bool flag=false;
        for (int i=0; i<cars.size(); i++)
            if (plate == cars[i].license_plate){
                flag = true;
                cout<<"License plate: "<<cars[i].license_plate<<endl;
                cout<<"Color: "<<cars[i].color<<endl;
                cout<<"Number wheels: "<<cars[i].num_wheels<<endl;
                cout<<"Owner: "<<cars[i].owner<<endl<<endl;
            }
        if (!flag)
            cout<<"No car with this plate"<<endl;
    }
    
    void cout_cars(){
        char* sort_plates[cars.size()];
        for (int i=0; i<cars.size(); i++)
            sort_plates[i] = cars[i].license_plate;
        int n,m,code;
        char*temp;
        for(n = 1; n<cars.size(); n++)
            for(m = 0; m<cars.size() - n; m++)
            {
                code = strcmp(sort_plates[m+1], sort_plates[m]);
                if (code<0)
                {
                    temp = sort_plates[m];
                    sort_plates[m]=sort_plates[m+1];
                    sort_plates[m+1] = temp;
                }
            }
        for (int i =0 ; i<cars.size(); i++)
            inform_by_plate(sort_plates[i]);
    }
    
    car get(){
        if (cars.size()<1){
            car obj = cars[0];
            cars.erase(cars.begin());
            return obj;
        }
        throw "Empty";
        car p;
        return p;
    }
};

int main() {
 
    return 0;
}
