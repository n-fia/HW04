#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BookManager {
private:
    vector<Book> books;

public:

    Book findBookByTitle(const string& title) {
        for (Book book : books) {
            if (book.title == title) {
                return book;
            }
        }
        return;
    }

    // 책 추가 메서드 (제목, 작가) {books 벡터 배열에 추가}
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
    }


    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }
        cout << "\n현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); ++i) {
            cout << "- " << books[i].title << " by " << books[i].author << std::endl;
        }
    }

    //제목을 기준으로 검색 후 출력 메서드
    void searchByTitle(const string& title) {
        for (const Book& book : books) {
            if (book.title == title) {
                std::cout << "\n- " << book.title << " by " << book.author << std::endl;
                return;
            }
        }
        std::cout << "제목 검색 내역 : 없음" << std::endl;
    }

    //작가명을 기준으로 검색 후 출력 메서드
    void searchByAuthor(const string& author) {
        for (const Book& book : books) {
            if (book.author == author) {
                std::cout << "\n- " << book.title << " by " << book.author << std::endl;
                return;
            }
        }
        std::cout << "작가 검색 내역 : 없음" << std::endl;
    }
};

class BorrowManager {
    unordered_map<string, int> stock;   //<제목(key), 값(value)>을 저장하는 map stock
    //Book* books;    //Book 객체를 가리키는 포인터 books

public:

    BorrowManager() {}

    //책이 추가될 때 책의 권수를 초기화하기 > main함수에서 사용함
    void initioalizeStock(const Book* book, int quanity = 3) {

        if (book == nullptr) {
            return;
        }

        stock[book->title] = quanity;
        cout << book->title << " by " << book->author << "책이 추가되었습니다." << endl;

    }

    //2개는 포인터
    //변수명 중복
    //중복 출력
    //여기서 문제 생겼나?
    void borrowBook(string title) {
        if (stock.find(title) == stock.end()) {
            cout << "책을 찾지 못했습니다. 다시 실행해주세요." << endl;
            return;
        }
        if (stock[title] > 0 ) {
            stock[title]--;
        }
        cout <<title<< "을(를) 대여했습니다." << endl;
    }

    void returnBook(string title) {
        if (stock.find(title) == stock.end()) {
            cout << "책을 찾지 못했습니다. 다시 실행해주세요." << endl;
            return;
        }
        if (stock[title] < 3) {
            stock[title]++;
        }
        cout << title << "을(를) 반납했습니다." << endl;
    }

    //대여 현황 출력
    void displayStock() {
        std::cout << "전체 도서 재고 현황 : \n" << std::endl;
        for (const auto& sto : stock) {
            cout << "책 제목 : " << sto.first << "책 재고 : " << sto.second << "권" << endl;
        }
        //for문
        //(pair 쓰시는데 : stock) // 키 값을 기준으로 하나봄
        //책 제목 + 맵.first << 책 재고 << 맵.second << endl;
    }
};

int main() {
    BookManager manager;
    BorrowManager borrowManager;

    manager.addBook("1번 도서", "1번 저자"); //그냥 string&이면 수정 가능한 객체를 넣어줘야 해서 문자열을 바로 못 넣는데, const string& str이니까 수정 안 되고 컴파일러가 알아서 임시적 객체를 생성해준다!
    manager.addBook("2번 도서", "2번 저자");
    borrowManager.initioalizeStock(&manager.findBookByTitle("1번 도서"));
    borrowManager.initioalizeStock(&manager.findBookByTitle("2번 도서"));

    system("cls"); // 콘솔 화면을 모두 지운다뭐지 우와 뭐 할 때마다 사라지고 나오고 미쳤음 겁나 샤프함

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {

        std::cout << "\n도서관 관리 프로그램" << std::endl;
        std::cout << "1. 책 추가" << std::endl; // 책 정보를 입력받아 책 목록에 추가
        std::cout << "2. 모든 책 출력" << std::endl; // 현재 책 목록에 있는 모든 책 출력
        std::cout << "3. 종료" << std::endl; // 프로그램 종료
        std::cout << "4. 도서 검색" << std::endl; // 제목/작가를 기준으로 검색
        std::cout << "5. 도서 대여" << std::endl; // 대여
        std::cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            //1 입력하고 엔터치면 1은 이동하는데 \n이 입력버퍼(출력으로 가기 전의 배열비슷?)에 남아있음 근데 담ㅁ에 getline을 하면 title을 안 받고 ]n을 인식하고 이동한다.
            //그래서 개행문자로 cin과 getline을 같이 사용할 때 ignore을 사용하자

            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            //책의 권수 3으로 초기화
            borrowManager.initioalizeStock(&manager.findBookByTitle(title));
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else if (choice == 4) {
            //4번 선택: 검색
            //작가나 제목을 검색하여 도서 정보를 출력합니다.
            string str;
            cout << "\n제목이나 작가를 입력하세요. : ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            std::getline(cin, str); // 저자명 입력 (공백 포함)
            manager.searchByTitle(str);
            manager.searchByAuthor(str);
        }
        else if (choice == 5) {
            //5번 선택: 대여
            //작가나 제목을 검색하여 도서 정보 + 대여권수를 출력합니다.
            string string;
            short n;
            cout << "\n제목을 입력하세요. : ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            std::getline(cin, string); // 제목/저자명 입력 (공백 포함)
            manager.searchByTitle(string);
            manager.searchByAuthor(string);
            //남은 권수는 search에서 알려주

            cout << "대여하시겠습니까? (1. 예 / 2. 아니오) : ";
            
            cin >> n;
            if (n == 1) {
                Book book = manager.findBookByTitle(string);
                    if (&book) {
                        //manager.borrowBooks(string);
                        borrowManager.borrowBook(string);
                    }
                    else {
                        cout << "해당하는 책이 없습니다." << endl;
                    }
            }
            else if (n == 2) {
                //그냥 끝
            }
            else {
                cout << "잘못된 입력입니다." << endl;
            }
        }
        else if (choice == 6) {

        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
        //system("pause"); //이거 머지
    }
    return 0; // 프로그램 정상 종료
}