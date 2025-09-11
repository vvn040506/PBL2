//Vi phạm
class Violation{
    private:
        string name; // lỗi vi phạm
        string date; // ngày vi phạm
        double fine; // mức phạt tiền
    public:
        Violation(); 
        void display();
        string getName();
        string getDate();
        double getFine();
        void setName(string);
        void setFine(double);
        void setDate(string);
};