#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct kuyrukVeriYapisi
{ 
	int oncelik;
	char isim[30];
	struct kuyrukVeriYapisi *sonraki;
};

kuyrukVeriYapisi *ilk=NULL,*son=NULL,*gecici=NULL;

void dosyadanOku(FILE *dosya){  									 //Dosyadan okunan verilerin s�ral� oldu�u kabul edilerek i�lem yap�l�yor
	while(!feof(dosya)){	
		gecici=(kuyrukVeriYapisi*)malloc(sizeof(kuyrukVeriYapisi));  //Dinamik olarak yer a��l�yor
		gecici->sonraki=NULL;
		fscanf(dosya,"%d %s",&gecici->oncelik,&gecici->isim);		 //�ncelik isim format�na uygun okuma yap�l�yor
		if(ilk==NULL){												 //E�er kuyruk bo�sa ilk olarak ba�a ekleniyor
			ilk=gecici;
			son=ilk;
		}
		else{														 //Kuyrukta eleman varsa sona ekleme yap�l�yor
			son->sonraki=gecici;
			son=gecici;
		}
	}
}

void listele(){                                                       //Kuyru�un ba��ndan sonuna kadar s�rayla gezilip �ncelik-isim format�na g�re ekrana yazd�r�l�yor
	printf("\n");
	gecici=ilk;
	printf(" �NCEL�K | �S�M\n");
	while(gecici!=NULL)
	{
		printf("    %d      %s\n",gecici->oncelik,gecici->isim);
		gecici=gecici->sonraki;
	}
	return ;
}

void klavyedenEkle()											 	  					//Kullan�c�n�n klavyeden girdi�i verilere g�re i�lem yap�l�p uygun yerlere ekleme yap�l�yor. 
{																	  					//Hali haz�rda dosyadan kay�t al�nd��� i�in kuyru�un bo� olmad��� varsay�l�yor.		
	kuyrukVeriYapisi *eklenecek=(kuyrukVeriYapisi*)malloc(sizeof(kuyrukVeriYapisi));	//Yeni kay�t i�in dinamik olarak yer a��l�yor
	eklenecek->sonraki=NULL;
	fflush(stdin);																		//Klavyeden giri� hatas�n� engellemek i�in input temizleniyor.
	printf("\n�ncelik giriniz ->");
	scanf("%d",&eklenecek->oncelik);
	fflush(stdin);
	printf("\n�sim giriniz ->");
	scanf("%s",&eklenecek->isim);
	gecici=ilk;
	int eklendi = 0;																	//Ekleme yap�l�p yap�lmad���n� belirten bayrak.
	while(gecici->sonraki!=NULL){
		if(gecici->oncelik <= eklenecek->oncelik && eklenecek->oncelik < gecici->sonraki->oncelik){  //Yeni kayd�n �nceli�i di�er kay�tlar ile kar��la�t�r�l�p uygun yere ekleme yap�l�yor.
			eklenecek->sonraki=gecici->sonraki;
			gecici->sonraki=eklenecek;
			eklendi = 1;																//Ekleme bayra�� 1 yap�l�yor.
			break;
		}
		gecici=gecici->sonraki;
	}
	if(eklendi==0){																		//Ekleme bayra�� 1 de�ilse ekleme yap�lamam��t�r. Kayd�n �nceli�i daha �nce eklenmi� bir �ncelik seviyesi
		gecici->sonraki=eklenecek;														//de�ildir. Dolay�s�yla sona ekleme yap�l�yor.
		eklenecek->sonraki=NULL;
	}
}

int siraBul(char *arananKayit)															//Kullan�c�n�n klavyeden girdi�i kay�t ismine g�re arama yap�l�yor.
{
	int sayac=0;
	gecici=ilk;
	while(gecici!=NULL)
	{
		if(!strcmp(strupr(arananKayit),strupr(gecici->isim)))							//strcmp fonksiyonu ile kar��la�t�rma yap�l�yor. strupr fonksiyonunun kullan�lma amac� kay�tlar� b�y�k harfe �evirip
		{																				//b�y�k k���k harf farkl�l���n� �nlemek. strupr yerine strlwr de kullan�labilir. Kay�tlar�n ilk aramadan sonra 
			return sayac;																//b�y�k harfe ge�mesinin sebebi bu fonksiyon.
		}
		else
		{
			sayac++;
			gecici=gecici->sonraki;
		}
	}
	return -1;
}
	
int main(){	
	setlocale(LC_ALL,"Turkish");					//T�rk�e karakterleri kullanabilmek i�in lokal dil se�ene�i.
    FILE *dosya = fopen("kayitlar.txt","r");
	dosyadanOku(dosya);
	fclose(dosya);
	int secim;
	while(1)
	{	
		printf("\n1.)L�STELE \n2.)KAYIT EKLE\n3.)SIRA BUL\n4.)PROGRAMI SONLANDIR...\n\nL�tfen se�im yap�n�z -> ");
		scanf("%d",&secim);
		switch (secim)
		{
	    	case 1:
		  	{
				if(ilk==NULL){
					printf("\nListe bo�. L�tfen kay�t ekleyiniz...\n");
					printf("\nDevam etmek i�in bir tu�a bas�n�z.\n");
					getch();
					system("CLS");
					break;	
				}else{
					listele();
					printf("\nDevam etmek i�in bir tu�a bas�n�z.\n");
					getch();
					system("CLS");
					break;
				} 
			}
			
	    	case 2:
		  	{
			  	klavyedenEkle();
				printf("\nEkleme tamamland�.\n");
				printf("\nDevam etmek i�in bir tu�a bas�n�z.\n");
				getch();
				system("CLS");
			  	break;
		  	}
			  	 
	      	case 3:
		  	{
				char arananKayit[20];
				printf("\nArad���n�z kayd�n ismini giriniz ->\n");
				scanf("%s",arananKayit);
				int sira = siraBul(arananKayit);
				if(sira==-1){
					printf("Arad���n�z isimde kay�t bulunamam��t�r.\n");
					printf("\nDevam etmek i�in bir tu�a bas�n�z.\n");
					getch();
					system("CLS");
					break;
				}
				else{
					printf("\nArad���n�z kayd�n �n�nde %d ki�i var.\n",sira);
					printf("\nDevam etmek i�in bir tu�a bas�n�z.\n");
					getch();
					system("CLS");
					break;
				}
		  	}
		  	
	      	case 4:
	      	{
		  		printf("\nPROGRAM SONLANDIRILIYOR\n");
		  		exit(0);
		  		break;
		  	}
		  	
	      	default:
			{
			printf("\nYANLI� SE��M YAPTINIZ. L�TFEN 1 - 4 ARASI SE��M YAPINIZ!!!\n");
			printf("\nDevam etmek i�in bir tu�a bas�n�z.\n");
			getch();
			system("CLS");
			break;
			}
		}
	}
	return 0;
}








