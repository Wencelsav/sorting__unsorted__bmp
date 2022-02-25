#include "Bmp.h"
using namespace std;
//читаем файл bmp и пишем в массивы значения цветов для каждого индекса
void read_bmp_pixels(int size, int* bleu, int* green, int* red, int* alfa, const char* name_and_path_start_bmp, int channels) {
	//открываем bmp файл
	BMP pict(name_and_path_start_bmp);
	//записываем значения цветов в соответсвующие массивы, для каждого цвета свой массив
	for (int i = 0; i < size; i++) {
		
		bleu[i] = pict.data[channels * i + 0];
		green[i] = pict.data[channels * i + 1];
		red[i] = pict.data[channels * i + 2];
		//проверяем есть ли альфа канал
		if (channels == 4) {
			alfa[i] = pict.data[channels * i + 3];
		}
	}
}
//читаем txt файл
void readtxt(int size, int input[], const char* name_and_path_txt) {
	ifstream f;
	//открываем файл
	f.open(name_and_path_txt);
	if (f.is_open())
	{
		for (int i = 0; i < size; i++)
		{//записываем числа в массив
			f >> input[i];
		}//закрываем файл
		f.close();
	}//если файл не открылся
	else {
		cout << "eror" << endl;
	}
}
void heapify(int* mas_to_sort, int n, int i, int* bleu, int* green, int* red, int* alfa)
{
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; // левый
	int r = 2 * i + 2; // правый
	// Если левый или правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (l < n /*проверка на выход за пределы массива*/ && mas_to_sort[l] >
			mas_to_sort[largest])//проверка входит ли левый элемент в размер массива и сравнение значений массива по индексам левого потомка и корня
			largest = l;
	if (r < n && mas_to_sort[r] > mas_to_sort[largest])//проверка входит ли правый элемент в размер массива и сравнение значений массива по индексам правого потомка и корня
		largest = r;
	// Если после сравнений самым большим элементом оказался потомок а не корень
	if (largest != i)
	{
		swap(mas_to_sort[i], mas_to_sort[largest]);// то мы меняем местами значения	текущего корня и одного из его потомков
			swap(bleu[i], bleu[largest]);//заодно и делая то же самое для каждого цвета
		swap(green[i], green[largest]);
		swap(red[i], red[largest]);
		swap(alfa[i], alfa[largest]);
		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(mas_to_sort, n, largest, bleu, green, red, alfa);
	}
}
//функция выполняющяя пирамидальную сортировку
void heapSort(int* mas_to_sort, int n, int* bleu, int* green, int* red, int* alfa)
{
	int i = n / 2 - 1;
	// Построение кучи (перегруппируем массив)
	while (i >= 0) {
			heapify(mas_to_sort, n, i, bleu, green, red, alfa);
			i--;
	}
	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец так же меняя местами и значения для массивов цветов
		swap(mas_to_sort[0], mas_to_sort[i]);
		swap(bleu[0], bleu[i]);
		swap(green[0], green[i]);
		swap(red[0], red[i]);
		swap(alfa[0], alfa[i]);
		// вызываем процедуру heapify на уменьшенной куче
		heapify(mas_to_sort, i, 0, bleu, green, red, alfa);
	}
}
void write_bmp(int x, int y, int* bleu, int* green, int* red, int* alfa, const char*
	name_and_path_new_bmp, int channels) {
	BMP outpict(x, y);
	int a = 255;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			//проверяем необходимость альфа канала
			if (channels == 4) {
				a = alfa[i * x + j];
			}
			//записываем по соответсвующим координатам в изображении цвет пикселя по значениям массивов
				outpict.set_pixel(i, j, bleu[x*y-j*x + i], green[x * y - j * x + i], red[x * y - j * x + i], a);
				//индекс x*y-j*x + i выбран так потому что при индексе j*x + i мы получаем зеркальное отображение картинки
		}
	}
	outpict.write(name_and_path_new_bmp);
}
int main() {
	int x, y, size;
	//путь к txt файлу с цифрами и его название
	const char* name_and_path_txt = "17.txt";
	//путь к файлу bmp и его название
	const char name_and_path_start_bmp[] = "17e.bmp";
	// название bmp файла который будет создан для конечного изображения и путь к нему
	const char name_and_path_new_bmp[] = "result picture2.bmp";
	//открываем файл bmp
	BMP pict(name_and_path_start_bmp);
	//получаем ширину файла bmp
	x = pict.bmp_info_header.width;
	//получаем высоту файла bmp
	y = pict.bmp_info_header.height;
	// считаем сколько всего пикселей в файле
	size = x * y;
	//считаем будет ли альфа канал отвечающий за прозрачность или нет. если равно 4 то будет в остальных случаях нет
		int channels = pict.bmp_info_header.bit_count / 8;
	//создаём массивы цветов для палитры bmp где на каждый индекс приходится своё значение в нужных цветах
	int* bleu = new int[size];
	int* green = new int[size];
	int* red = new int[size];
	int* alfa = new int[size];
	//создаем массив для цифр
	int* input = new int[size];
	//читаем txt файл
	readtxt(size, input, name_and_path_txt);
	//читаем bmp файл
	read_bmp_pixels(size, bleu, green, red, alfa, name_and_path_start_bmp, channels);
	//сортируем
	heapSort(input, size, bleu, green, red, alfa);
	//создаем новый файл и пишем в него попиксельно цвета
	write_bmp(x, y, bleu, green, red, alfa, name_and_path_new_bmp, channels);
	return 0;
}