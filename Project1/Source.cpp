#include "Bmp.h"
using namespace std;
//������ ���� bmp � ����� � ������� �������� ������ ��� ������� �������
void read_bmp_pixels(int size, int* bleu, int* green, int* red, int* alfa, const char* name_and_path_start_bmp, int channels) {
	//��������� bmp ����
	BMP pict(name_and_path_start_bmp);
	//���������� �������� ������ � �������������� �������, ��� ������� ����� ���� ������
	for (int i = 0; i < size; i++) {
		
		bleu[i] = pict.data[channels * i + 0];
		green[i] = pict.data[channels * i + 1];
		red[i] = pict.data[channels * i + 2];
		//��������� ���� �� ����� �����
		if (channels == 4) {
			alfa[i] = pict.data[channels * i + 3];
		}
	}
}
//������ txt ����
void readtxt(int size, int input[], const char* name_and_path_txt) {
	ifstream f;
	//��������� ����
	f.open(name_and_path_txt);
	if (f.is_open())
	{
		for (int i = 0; i < size; i++)
		{//���������� ����� � ������
			f >> input[i];
		}//��������� ����
		f.close();
	}//���� ���� �� ��������
	else {
		cout << "eror" << endl;
	}
}
void heapify(int* mas_to_sort, int n, int i, int* bleu, int* green, int* red, int* alfa)
{
	int largest = i;
	// �������������� ���������� ������� ��� ������
	int l = 2 * i + 1; // �����
	int r = 2 * i + 2; // ������
	// ���� ����� ��� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
	if (l < n /*�������� �� ����� �� ������� �������*/ && mas_to_sort[l] >
			mas_to_sort[largest])//�������� ������ �� ����� ������� � ������ ������� � ��������� �������� ������� �� �������� ������ ������� � �����
			largest = l;
	if (r < n && mas_to_sort[r] > mas_to_sort[largest])//�������� ������ �� ������ ������� � ������ ������� � ��������� �������� ������� �� �������� ������� ������� � �����
		largest = r;
	// ���� ����� ��������� ����� ������� ��������� �������� ������� � �� ������
	if (largest != i)
	{
		swap(mas_to_sort[i], mas_to_sort[largest]);// �� �� ������ ������� ��������	�������� ����� � ������ �� ��� ��������
			swap(bleu[i], bleu[largest]);//������ � ����� �� �� ����� ��� ������� �����
		swap(green[i], green[largest]);
		swap(red[i], red[largest]);
		swap(alfa[i], alfa[largest]);
		// ���������� ����������� � �������� ���� ���������� ���������
		heapify(mas_to_sort, n, largest, bleu, green, red, alfa);
	}
}
//������� ����������� ������������� ����������
void heapSort(int* mas_to_sort, int n, int* bleu, int* green, int* red, int* alfa)
{
	int i = n / 2 - 1;
	// ���������� ���� (�������������� ������)
	while (i >= 0) {
			heapify(mas_to_sort, n, i, bleu, green, red, alfa);
			i--;
	}
	// ���� �� ������ ��������� �������� �� ����
	for (int i = n - 1; i >= 0; i--)
	{
		// ���������� ������� ������ � ����� ��� �� ����� ������� � �������� ��� �������� ������
		swap(mas_to_sort[0], mas_to_sort[i]);
		swap(bleu[0], bleu[i]);
		swap(green[0], green[i]);
		swap(red[0], red[i]);
		swap(alfa[0], alfa[i]);
		// �������� ��������� heapify �� ����������� ����
		heapify(mas_to_sort, i, 0, bleu, green, red, alfa);
	}
}
void write_bmp(int x, int y, int* bleu, int* green, int* red, int* alfa, const char*
	name_and_path_new_bmp, int channels) {
	BMP outpict(x, y);
	int a = 255;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			//��������� ������������� ����� ������
			if (channels == 4) {
				a = alfa[i * x + j];
			}
			//���������� �� �������������� ����������� � ����������� ���� ������� �� ��������� ��������
				outpict.set_pixel(i, j, bleu[x*y-j*x + i], green[x * y - j * x + i], red[x * y - j * x + i], a);
				//������ x*y-j*x + i ������ ��� ������ ��� ��� ������� j*x + i �� �������� ���������� ����������� ��������
		}
	}
	outpict.write(name_and_path_new_bmp);
}
int main() {
	int x, y, size;
	//���� � txt ����� � ������� � ��� ��������
	const char* name_and_path_txt = "17.txt";
	//���� � ����� bmp � ��� ��������
	const char name_and_path_start_bmp[] = "17e.bmp";
	// �������� bmp ����� ������� ����� ������ ��� ��������� ����������� � ���� � ����
	const char name_and_path_new_bmp[] = "result picture2.bmp";
	//��������� ���� bmp
	BMP pict(name_and_path_start_bmp);
	//�������� ������ ����� bmp
	x = pict.bmp_info_header.width;
	//�������� ������ ����� bmp
	y = pict.bmp_info_header.height;
	// ������� ������� ����� �������� � �����
	size = x * y;
	//������� ����� �� ����� ����� ���������� �� ������������ ��� ���. ���� ����� 4 �� ����� � ��������� ������� ���
		int channels = pict.bmp_info_header.bit_count / 8;
	//������ ������� ������ ��� ������� bmp ��� �� ������ ������ ���������� ��� �������� � ������ ������
	int* bleu = new int[size];
	int* green = new int[size];
	int* red = new int[size];
	int* alfa = new int[size];
	//������� ������ ��� ����
	int* input = new int[size];
	//������ txt ����
	readtxt(size, input, name_and_path_txt);
	//������ bmp ����
	read_bmp_pixels(size, bleu, green, red, alfa, name_and_path_start_bmp, channels);
	//���������
	heapSort(input, size, bleu, green, red, alfa);
	//������� ����� ���� � ����� � ���� ����������� �����
	write_bmp(x, y, bleu, green, red, alfa, name_and_path_new_bmp, channels);
	return 0;
}