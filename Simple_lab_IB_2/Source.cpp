#include <iostream>
#include <string>

struct MyData{
	std::string
		nickname       = "",
		password       = "",
		surname        = "",
		name           = "",
		patronymic     = "",
		Date_of_Birth  = "",
		Place_of_Birth = "",
		phone_num      = "";
};
MyData* people = new MyData[5];
void main();

// Проверяем наличие пользовотеля с веденными данными
bool CheckForAvailability(std::string nick, std::string pas, int& id) {
	for (int i = 0; i != 5; i++)				// Проходим по всем юзерам,
		if (people[i].nickname == nick)			// если есть совпадение ника 
			if (people[i].password == pas) {	// и пароля,
				id = i;							// запоминаем номер пользвотеля
				return true;					// и возвращаем истину что юзер найден
				break;
			}

	return false;								// иначе юзер не найден
}

// Меняем пароль
std::string newPassword(std::string pas, int id) {
	system("cls");
	std::string old_pas, new_pas1, new_pas2;

EnterNewPas: //метка ввода нового пароля

	std::cout << "\t\t\tPassword change " << std::endl << std::endl;
	std::cout << "Enter old password: **********\b\b\b\b\b\b\b\b\b\b";
		std::cin >> old_pas;
	std::cout << "Enter new password: **********\b\b\b\b\b\b\b\b\b\b";
		std::cin >> new_pas1;
	std::cout << "Enter new password (repeat): **********\b\b\b\b\b\b\b\b\b\b";
		std::cin >> new_pas2;

	if (new_pas1 != new_pas2) {
		std::cout << "\tERROR: New password mismatch!" << std::endl;
		goto EnterNewPas;
	}
	if (new_pas1.length() != 10 || new_pas2.length() != 10) {
		std::cout << "\tERROR: New password < 10 characters!" << std::endl;
		goto EnterNewPas;
	}
	if (old_pas != pas) {
		std::cout << "\tERROR: Old password mismatch!" << std::endl;
		goto EnterNewPas;
	}
	std::cout << "\tDONE:Password changed successfully!" << std::endl;
	return new_pas1;
}

//Вход
void Entrance() {
	system("cls");
	std::string nickname, password;

	std::cout << "\t\t\tAuthorization " << std::endl << std::endl;
	std::cout << "Enter nickname:";
		std::cin >> nickname;
	std::cout << "Enter password: **********\b\b\b\b\b\b\b\b\b\b";
		std::cin >> password;

	int id = 0; // Будем запоминать номер пользовотеля
	bool flag = CheckForAvailability(nickname, password, id);

	if (flag) people[id].password = newPassword(password, id);
	else {
		std::cout << "\tERROR: User not faund" << std::endl;

		for (int i = 0; i != 5; i++) 
			if (people[i].nickname != "") { // Если поле юзера не пустое то
				// меняем последнюю букву на след-ю по алфавиту
				if (people[i].password[10] == 'z') people[i].password[4] = 'a';
				else people[i].password[10] += 1;
			}
	}
	main();// Возвращаемся в мейн
}

// Поиск свободного места в массиве
int SearchForPlace() {
	for (int i = 0; i < 5; i++) // Проходимся по всему массиву
	if (people[i].nickname == "") return i; // если поле Никнейма пустое, вернём значение id
	
	return 4; // если пустых мест нет, перезапишем последнего юзера
}

// Регистрация
void Register() {
	system("cls");//очищаем поле
	std::cout << "\t\t\tRegistration " << std::endl << std::endl;
	int id = SearchForPlace();// Получаем значение свободного места в массиве структуры
	std::cout << "Enter nickname:";
		std::cin >> people[id].nickname;
	std::cout << "Enter password:";
		std::cin >> people[id].password;

	while (people[id].password.length() != 10) {
		std::cout << "\tERROR: Password >10 characters!" << std::endl;
		std::cout << "\nEnter password:";
			std::cin >> people[id].password;
	}
	main();// Возвращаемся в мейн
}

// Просмотр всех юзеров
void GetAll() {
	system("cls");
	std::cout << "All Users:" << std::endl;
	// Проверить что изменения прошли
	for (int i = 0; i != 5; i++)
		std::cout << people[i].nickname << "\t" << people[i].password << std::endl;
	system("pause");
	main();// Возвращаемся в мейн
}

// Выбор перехода 
void Choice() {
	system("cls");
	int var = 0;
	std::cout << "Register(1) or Entrance(2) or View base(3) and Exit(4)?" << std::endl;
	std::cin >> var;

	if (var == 1) Register();
	if (var == 2) Entrance();
	if (var == 3) GetAll();
	else exit(0);
}

void main() {
	Choice();
	system("pause");
}