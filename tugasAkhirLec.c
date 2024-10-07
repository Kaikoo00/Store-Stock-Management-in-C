#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char PATH[]="./TokoSumberSejahtera.txt"; //alamat dari file yang akan digunakan dalam seluruh sistem

typedef struct produk{ //struct yang menyimpan atribut tiap jenis item
	char namaProduk[30];
	char tanggalPenerimaan[15];
	int stok;
	float harga;
	float totalUang;
}product;

void showMenu(){ //tampilkan menu di terminal untuk user
	printf("==================MENU==================\n");
	printf("1. Buat file baru\n");
	printf("2. Tambahkan data produk\n");
	printf("3. Ganti data produk yang sudah ada\n");
	printf("4. Hapus data produk\n");
	printf("5. Tampilkan list produk\n");
	printf("6. Sortir bedasarkan harga\n");
	printf("7. Sortir bedasarkan jumlah stok\n");
	printf("8. Cari produk bedasarkan nama produk\n");
	printf("0. Exit Program\n");
}

void create(){ //membuat file baru yang sepenuhnya kosong, untuk menyimpan data yang disimpan user
	system("cls");
	FILE *fp; //file pointer untuk membuka file yang akan digunakan
	product temp; //struct yang akan digunakan untuk menulis dalam file
	fp = fopen(PATH, "w");
	printf("Berapa jenis produk yang ingin anda masukkan?\n>");
	int jumlah; scanf("%d", &jumlah);getchar(); //meminta user memasukkan jumlah data yang ingin dimasukkan
	for(int i=0; i<jumlah; i++){ //loop untuk input data 
		printf("Masukkan nama produk\n>");
		scanf("%[^\n]",temp.namaProduk);getchar();
		printf("Masukkan tanggal penerimaan produk(dd/mm/yyyy)\n>");
		scanf("%[^\n]",temp.tanggalPenerimaan);getchar();
		printf("Berapa stok yang tersedia saat ini?\n>");
		scanf("%d",&temp.stok);getchar();
		printf("Berapa harga produk tersebut?\n>");
		scanf("%f",&temp.harga);getchar();
		temp.totalUang = temp.harga * temp.stok;
		fprintf(fp, "%s;%s;%d;%.2f;%f\n",temp.namaProduk,temp.tanggalPenerimaan,temp.stok,temp.harga,temp.totalUang);	
		system("cls");
	}
	fclose(fp);
}

void append(){ //membuka file lama dan menambahkan item baru ke dalam file tersebut
	system("cls");
	FILE *fp;
	product temp; //struct yang akan digunakan
	fp = fopen(PATH, "a"); //buka file dengan mode "a" agar isi file yang lama tidak hilang
	printf("Berapa jenis produk yang ingin anda tambahkan?\n>");
	int jumlah; scanf("%d", &jumlah);getchar(); //meminta user memasukkan jumlah barang yang ingin ditambahkan
	for(int i=0; i<jumlah; i++){ //loop input data
		printf("Masukkan nama produk\n>");
		scanf("%[^\n]",temp.namaProduk);getchar();
		printf("Masukkan tanggal penerimaan produk(dd/mm/yyyy)\n>");
		scanf("%[^\n]",temp.tanggalPenerimaan);getchar();
		printf("Berapa stok yang tersedia saat ini?\n>");
		scanf("%d",&temp.stok);getchar();
		printf("Berapa harga produk tersebut?\n>");
		scanf("%f",&temp.harga);getchar();
		temp.totalUang = temp.harga * temp.stok;
		fprintf(fp, "%s;%s;%d;%.2f;%.2f\n",temp.namaProduk,temp.tanggalPenerimaan,temp.stok,temp.harga,temp.totalUang);	
		system("cls");
	}
	fclose(fp);
}

void display(){	//menampilkan data yang sudah ada dalam bentuk tabel di terminal
	system("cls");
	FILE *fp;
	product temp; //struct yang akan digunakan untuk print
	fp = fopen(PATH, "r"); //membuka file dengan mode "r" untuk mengambil data dari dalam file
	printf("================================================================================   \n");
    printf("||     Nama Produk|  Tgl Penerimaan|       Stok|       Harga|            Total||   \n");
    printf("================================================================================   \n");
    //loop yang digunakan untuk menampilkan data yang sudah ada
	while(fscanf(fp,"%[^;];%[^;];%d;%f;%f\n",temp.namaProduk,temp.tanggalPenerimaan,&temp.stok,&temp.harga,&temp.totalUang)!=EOF){
		printf("||%16s|      %10s| %10d|%12.1f|%17.1f||\n",temp.namaProduk,temp.tanggalPenerimaan,temp.stok,temp.harga,temp.totalUang);
		printf("--------------------------------------------------------------------------------\n");
	}
	fclose(fp);
}

void modify(){ //fungsi untuk mengubah data yang sudah ada
	system("cls");
	display();
	FILE *fp, *fp1;
	int found; //variabel untuk menyatakan apakah data yang ingin diubah ada atau tidak
	product temp; //struct yang akan digunakan untuk mengubah data dan menulis dalam file
	fp = fopen(PATH, "r"); //buka file lama dengan mode "r" untuk mengambil data
	fp1 = fopen("temp.txt","w"); //buka file baru sementara dengan mode "w" untuk menulis data yang sudah diubah
	printf("\nProduk apa yang ingin diganti datanya?\n>"); //meminta user memasukkan nama dari data yang ingin diubah atributnya
	char tempNamaProd[30]; scanf("%[^\n]", tempNamaProd); getchar();
	while(fscanf(fp,"%[^;];%[^;];%d;%f;%f\n",temp.namaProduk,temp.tanggalPenerimaan,&temp.stok,&temp.harga,&temp.totalUang)!=EOF){
		if(strcmp(tempNamaProd, temp.namaProduk)==0&&found==0){ //mengecek apakah data yang discan, sama dengan input user, jika sama maka 
			printf("Masukkan tanggal penerimaan produk(dd/mm/yyyy)\n>"); //if statement ini akan dijalankan
			scanf("%[^\n]", temp.tanggalPenerimaan);getchar(); //if statement ini berisi input data baru
			printf("Berapa stok yang tersedia saat ini?\n>");
			scanf("%d", &temp.stok);getchar();
			printf("Berapa harga produk tersebut?\n>");
			scanf("%f",&temp.harga);getchar();
			temp.totalUang = temp.stok*temp.harga;
			found = 1;
		}
		fprintf(fp1, "%s;%s;%d;%.2f;%.2f\n",temp.namaProduk,temp.tanggalPenerimaan,temp.stok,temp.harga,temp.totalUang); //data ditulis di file baru
	}
	fclose(fp);
	fclose(fp1);
	if(found==1){
		printf("Succeed\n");
	}		
	else{
		printf("Benda tidak tersedia dalam stok\nDaftarkan benda ke dalam stok sebelum mengubah data yang sudah ada.\n");
		system("pause");
	}
	remove("TokoSumberSejahtera.txt"); //menghapus file lama
	rename("temp.txt","TokoSumberSejahtera.txt"); //mengubah nama file baru menjadi "TokoSumberSejahtera.txt"
	fp = fopen("TokoSumberSejahtera.txt","r");
	fclose(fp);
	display();
	system("pause");
	system("cls");
}

void deleteData(){ //konsepnya sama dengan modify data
	system("cls"); //yang berbeda adalah isi if statementnya
	FILE *fp, *fp1; //dalam deletedata, data yang ingin dihapus, akan dilewati dan tidak ditulis ulang dalam file baru
	int found; //sehingga data tersebut tidak akan ada difile yang sudah diubah
	product temp;
	fp = fopen(PATH, "r");
	fp1 = fopen("temp.txt","w");
	display();
	printf("\nProduk apa yang ingin dihapus datanya?\n>");
	char tempNamaProd[30]; scanf("%[^\n]", tempNamaProd); getchar();
	while(fscanf(fp,"%[^;];%[^;];%d;%f;%f\n",temp.namaProduk,temp.tanggalPenerimaan,&temp.stok,&temp.harga,&temp.totalUang)!=EOF){
		if(strcmp(tempNamaProd, temp.namaProduk)==0&&found==0){
			found = 1;
			continue;
		}
		fprintf(fp1, "%s;%s;%d;%.2f;%.2f\n",temp.namaProduk,temp.tanggalPenerimaan,temp.stok,temp.harga,temp.totalUang);
	}
	fclose(fp);
	fclose(fp1);
	if(found==1){
		printf("Succeed\n");
	}		
	else{
		printf("Benda tidak tersedia dalam stok\nDaftarkan benda ke dalam stok sebelum mengubah data yang sudah ada.\n");
		system("pause");
	}
	remove("TokoSumberSejahtera.txt");
	rename("temp.txt","TokoSumberSejahtera.txt");
	fp = fopen("TokoSumberSejahtera.txt","r");
	fclose(fp);
	display();
	system("pause");
	system("cls");
}

void sortByPrice(){ //fungsi untuk mengsortir data bedasarkan harganya
	int n; //variabel untuk menghitung jumlah data
	product temp[100]; //array of struct yang digunakan untuk menyimpan seluruh data
	product test; //variabel untuk menukar elemen dari array of struct
	FILE *fp; fp=fopen(PATH, "r");
	while(fscanf(fp,"%[^;];%[^;];%d;%f;%f\n",temp[n].namaProduk,temp[n].tanggalPenerimaan,&temp[n].stok,&temp[n].harga,&temp[n].totalUang)!=EOF){
		n++; //untuk setiap pengulangan while loop ini, jumlah data ditambah satu.
	}
	fclose(fp);
	int i, j;
    for (i = 0; i < n - 1; i++){ //sort ini menggunakan logika bubble sort akan tetapi
    	for (j = 0; j < n - i - 1; j++){ //yang ditukar adalah elemen struct
			if (temp[j].harga > temp[j + 1].harga){
				test=temp[j];
				temp[j]=temp[j+1];
				temp[j+1]=test;
			}		
		}
	}
	fp = fopen(PATH, "w");
	for(int i=0; i<n; i++){ //loop untuk menulis ulang data yang sudah disortir
		fprintf(fp, "%s;%s;%d;%.2f;%.2f\n", temp[i].namaProduk, temp[i].tanggalPenerimaan, temp[i].stok, temp[i].harga, temp[i].totalUang);
	}
	fclose(fp);
	display();
	system("pause");
	system("cls");
}

void sortByStok(){ //konsepnya sama dengan sortByPrice, tapi yang membedakan adalah
	int n;		   //if statement pada bubblesortnya, didalam fungsi sortByStok
	product temp[100]; //yang digunakan dalam if statement nya adalah jumlah stok yang tersedia
	product test;
	FILE *fp; fp=fopen(PATH, "r");
	while(fscanf(fp,"%[^;];%[^;];%d;%f;%f\n",temp[n].namaProduk,temp[n].tanggalPenerimaan,&temp[n].stok,&temp[n].harga,&temp[n].totalUang)!=EOF){
		n++;
	}
	fclose(fp);
	int i, j;
    for (i = 0; i < n - 1; i++){
    	for (j = 0; j < n - i - 1; j++){
			if (temp[j].stok > temp[j + 1].stok){
				test=temp[j];
				temp[j]=temp[j+1];
				temp[j+1]=test;
			}		
		}
	}
	fp = fopen(PATH, "w");
	for(int i=0; i<n; i++){
		fprintf(fp, "%s;%s;%d;%.2f;%.2f\n", temp[i].namaProduk, temp[i].tanggalPenerimaan, temp[i].stok, temp[i].harga, temp[i].totalUang);
	}
	fclose(fp);
	display();
	system("pause");
	system("cls");
}

void searchByName(){ //konsepnya sama dengan modify data
	system("cls"); //yang berbeda adalah isi if statementnya
	FILE *fp, *fp1; //dalam searchByName, apabila data yang dicari ketemu, akan ditampilkan di terminal
	int found; //apabila tidak ketemu, sistem akan menampilkan pesan kalau data yang dicari tidak ada
	product temp;
	fp = fopen(PATH, "r");
	fp1 = fopen("temp.txt","w");
	display();
	printf("\nProduk apa yang anda cari?\n>");
	char tempNamaProd[30]; scanf("%[^\n]", tempNamaProd); getchar();
	system("cls");
	printf("================================================================================   \n");
   	printf("||     Nama Produk|  Tgl Penerimaan|       Stok|       Harga|            Total||   \n");
    printf("================================================================================   \n");		
	while(fscanf(fp,"%[^;];%[^;];%d;%f;%f\n",temp.namaProduk,temp.tanggalPenerimaan,&temp.stok,&temp.harga,&temp.totalUang)!=EOF){
		if(strcmp(tempNamaProd, temp.namaProduk)==0){
			printf("||%16s|      %10s| %10d|%12.1f|%17.1f||\n",temp.namaProduk,temp.tanggalPenerimaan,temp.stok,temp.harga,temp.totalUang);
			printf("--------------------------------------------------------------------------------\n");
			found = 1;
		}
	}
	if(!found){
		system("cls");
		printf("Produk yang anda cari tidak tersedia.\n");
	}
	system("pause");
	system("cls");
}

int main(){
	int ch;
	while(1){
		showMenu(); //fungsi tampilan menu
		printf("\nApa yang mau anda lakukan hari ini?\n>");
		scanf("%d",&ch);getchar(); //minta input nomor fungsi yang akan digunakan oleh user
		switch(ch){
			case 1:
				create();
				break;
			case 2:
				append();
				break;
			case 3:
				modify();
				break;
			case 4:
				deleteData();
				break;
			case 5:
				display();
				system("pause");
				system("cls");
				break;
			case 6:
				sortByPrice();
				break;
			case 7:
				sortByStok();
				break;
			case 8:
				searchByName();
				break;
			case 0:
				system("cls");
				printf("Terimakasih sudah menggunakan aplikasi ini!\n");
				exit(0);
			default:
				printf("Menu tidak tersedia\n");
				system("pause");
				system("cls");
				break;
		}
	}
	return 0;
}
