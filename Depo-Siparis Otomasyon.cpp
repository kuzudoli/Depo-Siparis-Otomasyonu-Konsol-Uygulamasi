#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
using namespace std;
class hesap1{
	private:
		char urunID[4];
		char urunADET[5];
		char urunISMI[30];
		string okunan,eslesme,eslesme2;
		string idokunan,idokunan2;
		string id_donustur;
		string listeoku;
	public:
		//BAÞLIKLARI YAZDIRMAK ÝÇÝN YAPICI FONKSÝYON
		hesap1(){
			string baslikoku="";
			int satir=0;
			ofstream baslik_yazdir("urun_bilgi.txt",ios::app);
			baslik_yazdir.setf(ios::left);
			ifstream baslik("urun_bilgi.txt");
			while(!baslik.eof()){
				satir++;
				getline(baslik,baslikoku);
				if(satir==1 && baslikoku==""){
					baslik_yazdir << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET" << endl;
					baslik_yazdir.close();
				}
				else{
					break;
				}
			}	
		}
		~hesap1(){
		}
		void setisim(char y_isim[30]){
			for(int i=0;i<30;i++){
				urunISMI[i]=y_isim[i];
			}
		}
		void setadet(char y_adet[5]){
			for(int i=0;i<5;i++){
				urunADET[i]=y_adet[i];
			}
		}
		void ekle(){
			int idsayi;
			int adetSayi;
			ofstream urun_bilgi("urun_bilgi.txt",ios::app);
			int sayac=0,dogruluk=0;
			ifstream id_bak("urun_bilgi.txt");
			int s_sayi=0;
			
			//ÜRÜN ID ATAMAK ÝÇÝN
			while(!id_bak.eof()){
				s_sayi++;
				sayac++;	
				getline(id_bak,idokunan);
				id_donustur=idokunan.substr(0,4);
				for(int i=0;i<4;i++){
					urunID[i]=id_donustur[i];
				}
				urun_bilgi.setf(ios::left);
				if(sayac==2){
					//DOSYA BOÞ ÝSE ÝLK ID OLARAK 1000 ATANIYOR
					if(strlen(urunID)==0){
						dogruluk=1;
						urun_bilgi << setw(12) << "1000";
					}
				}
			}
			id_bak.close();
			int s_sayi2=0;
			ifstream id_bak2("urun_bilgi.txt");
			while(!id_bak2.eof()){
				s_sayi2++;
				getline(id_bak2,idokunan2);
				//SON SATIR BOÞ OLDUÐU ÝÇÝN BÝR ÖNCEKÝ SATIRIN ÝD DEGERÝNÝ OKUYOR VE BÝR ARTTIRARAK YENÝ ID OLUSTURUYOR
				if(s_sayi2==(s_sayi-1)){
					id_donustur=idokunan2.substr(0,4);
					for(int i=0;i<4;i++){
						urunID[i]=id_donustur[i];
					}
				idsayi=atoi(urunID);
				adetSayi=atoi(urunADET);
				if(dogruluk==0){
					urun_bilgi << setw(12) << (idsayi-adetSayi)/1000+1;
				}
				}
			}
			//GÜNCELLEME ESNASINDA ÝLK HARFÝ ALMIYOR
			urun_bilgi<< setw(30) << urunISMI << setw(10) << urunADET << endl;
			cout << "Ürün baþarýyla kaydedildi!\n";
			urun_bilgi.close();		
		}
		void listele(){
			//KAYITLI ÜRÜNLER EKRANA YAZDIRILIYOR
			ifstream listele("urun_bilgi.txt");
			while(!listele.eof()){
				getline(listele,listeoku);
				cout << listeoku << endl;
			}
			listele.close();
		}
		
		void ara(int secim2,int isim_kontrol){
			int id_kontrol;
			int hata=0;
			if(secim2==1){
				//ID NO ÝLE ARAMA YAPILIYOR
				do{
					cout << "Ürün ID: "; cin >> urunID; cin.ignore();
					id_kontrol=strlen(urunID);
					if(id_kontrol!=4) cout << "Lütfen geçerli ID giriniz!\n";
				}while(id_kontrol!=4);
				//URUN DOSYADAN OKUNUYOR VE KONTROL ÝSLEMÝ YAPILIYOR
				ifstream urunid_oku("urun_bilgi.txt");
				while(!urunid_oku.eof()){
					getline(urunid_oku,okunan);
					eslesme=okunan.substr(0,4);
					if (eslesme==urunID){
						hata=1;
						cout.setf(ios::left);
						cout << endl << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET" << endl;
						cout << okunan <<endl << endl;
					}
				}
				if(hata==0) cout << "Bu ID numarasýna ait ürün bulunamadý!" << endl;
				urunid_oku.close();
			}
			if(secim2==2){
				//ÜRÜN ÝSMÝ ÝLE ARAMA YAPILIYOR
				do{
					cout << "Ürün Ýsmi: "; cin.ignore(); gets(urunISMI); strlwr(urunISMI);
					isim_kontrol=strlen(urunISMI);
					if(isim_kontrol>25) cout << "Lütfen geçerli ürün ismi giriniz!\n";
				}while(isim_kontrol>25);
				cout.setf(ios::left);
				cout << endl << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET" << endl;
				//ÜRÜN DOSYADAN OKUNUYOR VE KONTROL ÝÞLEMÝ YAPILIYOR
				int onay=0;
				string gonder;
				ifstream urunisim_oku("urun_bilgi.txt");
				while(!urunisim_oku.eof()){
					getline(urunisim_oku,okunan);			
					for(int i=12;i<(12+strlen(urunISMI));i++){
						gonder+=okunan[i];	
					}
					if(urunISMI==gonder){
						cout << okunan << endl << endl;
						onay=1;
						//ÖNCEKÝ BÝLGÝNÝN ÜSTÜNE YAZMAMASI ÝÇÝN DEÐÝÞKEN TEMÝZLENÝYOR
						gonder="";
					}
					//ÖNCEKÝ BÝLGÝNÝN ÜSTÜNE YAZMAMASI ÝÇÝN DEÐÝÞKEN TEMÝZLENÝYOR
					else{
						gonder="";
					}
				}
				if(onay==0) cout << "-Aradýðýnýz ürüne ait bir kayýt bulunamadý-" << endl;
				urunisim_oku.close();
			}
		}
}urun;

class hesap2{
	private:
		char urunID[4];
		char urunADET[5];
		char urunISMI[30];
		string okunan,eslesme,eslesme2;
		string idokunan,idokunan2;
		string id_donustur;
		string listeoku;
		//SÝPARÝÞ DEÐÝÞKENLERÝ
		char s_urunID[4];
		int s_urunADET;
		int s2_urunADET;
		char k_sirketi[10];
		char siparisID[6];
		string s_okunan;
	public:
		string sip_id;
		int id_kontrol;
		//BAÞLIKLARI YAZDIRMAK ÝÇÝN YAPICI FONKSÝYON
		hesap2(){
			string baslikoku="";
			int satir=0;
			ofstream baslik_yazdir("siparis_bilgi.txt",ios::app);
			baslik_yazdir.setf(ios::left);
			ifstream baslik("siparis_bilgi.txt");
			while(!baslik.eof()){
				satir++;
				getline(baslik,baslikoku);
				if(satir==1 && baslikoku==""){
					baslik_yazdir << setw(15) << "SIPARIS ID" << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET"  << setw(12) << "KARGO S."<< endl;
					baslik_yazdir.close();
				}
				else{
					break;
				}
			}	
		}
		~hesap2(){
		}
	void sil(){
		//ÜRÜN SÝLME ÝÞLEMÝ YAPILIYOR
		//DIÞARIDAN GÝRÝLEN ID DIÞINDAKÝ BÜTÜN SATIRLAR BAÞKA DOSYAYA YAZDIRILIYOR BÖYLECE ÝSTENÝLEN ÜRÜN SÝLÝNMÝÞ OLUYOR
		do{
				cout << "Ürün ID: "; cin >> urunID; cin.ignore();
				id_kontrol=strlen(urunID);
				if(id_kontrol!=4) cout << "Lütfen geçerli ID giriniz!\n";
			}while(id_kontrol!=4);
			system("cls");		
			
			ifstream dosyaoku("urun_bilgi.txt");
			while(!dosyaoku.eof()){
				getline(dosyaoku,okunan);
				eslesme=okunan.substr(0,4);
		//ESLESME YOKSA BAÞKA DOSYAYA YAZDIR
				if(urunID!=eslesme){
					//BÝR SATIR BOÞLUK BIRAKMASINI ENGELLEMEK ÝÇÝN
					if(okunan!=""){
						ofstream yenidosya("yenibilgi.txt",ios::app);
						yenidosya << okunan << endl;
						yenidosya.close();
					}
				}
			}
			dosyaoku.close();
			//ÝLK DOSYA SÝLÝNÝYOR
			remove("urun_bilgi.txt");
			//perror("hata: "); // HATA KODUNU GÖSTERÝYOR
			//YENÝ DOSYANIN ADINI ÝLK DOSYANIN ADIYLA DEÐÝÞTÝRÝYOR BÖYLECE MAIN DOSYAMIZ OLARAK DEVAM EDÝYOR
			rename("yenibilgi.txt","urun_bilgi.txt");
			cout << "Ürün baþarýyla silindi\n";
	}
	void guncelle(){
		//ÜRÜN GÜNCELLEME
		do{
				cout << "Güncellemek Ýstediðiniz Ürünün ID NUMARASINI Giriniz: "; cin >> urunID; cin.ignore();
				id_kontrol=strlen(urunID);
				if(id_kontrol!=4) cout << "Lütfen geçerli ID giriniz!\n";
			}while(id_kontrol!=4);
			system("cls");		
			ifstream dosyaoku("urun_bilgi.txt");
			while(!dosyaoku.eof()){
				getline(dosyaoku,okunan);
				eslesme=okunan.substr(0,4);
		//ESLESME YOKSA BAÞKA DOSYAYA YAZDIR
				if(urunID!=eslesme){
					//BÝR SATIR BOÞLUK BIRAKMASINI ENGELLEMEK ÝÇÝN
					if(okunan!=""){
						ofstream yenidosya("yenibilgi.txt",ios::app);
						yenidosya << okunan << endl;
						yenidosya.close();
					}
				}
				
				else if(urunID==eslesme){
					eslesme2=urunID;
				}				
			}
			dosyaoku.close();
			remove("urun_bilgi.txt");
			rename("yenibilgi.txt","urun_bilgi.txt");
			
			//ÜRÜN KAYIT
			ofstream urun_bilgi("urun_bilgi.txt",ios::app);
			urun_bilgi.setf(ios::left);
			do{
				cout << "YENÝ Ürün Ýsmi: "; cin.ignore(); gets(urunISMI); strlwr(urunISMI);
				if(urunISMI=="") cout << "Lutfen isim alanýný boþ býrakmayýnýz..." << endl;
			}while(urunISMI=="");
			
			do{
				cout << "YENÝ Ürün Adet: "; gets(urunADET);
				if(urunADET=="") cout << "Lütfen adet alanýný boþ býrakmayýnýz..." << endl;
			}while(urunADET=="");	
			urun_bilgi << setw(12) << eslesme2 <<setw(30) << urunISMI << setw(10) << urunADET << endl;
			cout << "Ürün baþarýyla güncellendi!\n";	
			urun_bilgi.close();
	}
	void setid2(){
		//ÝLK SÝPARÝÞ ID ATAMASI YAPILIYOR
		sip_id="813278";
	}
	void sipariskayit(){
			int onaylama=0;
			int sayac=0;
			int dogruluk=0;
			int idsayi2=0;
		//SÝPARÝÞ KAYIT
			ofstream siparis_bilgi("siparis_bilgi.txt",ios::app);
			siparis_bilgi.setf(ios::left);
			do{
				cout << "Sipariþ Kaydý Ýçin Ürün ID Giriniz: "; cin.ignore(); gets(s_urunID);
				ifstream kontrol("urun_bilgi.txt");
				while(!kontrol.eof()){
					getline(kontrol,idokunan);
					eslesme=idokunan.substr(0,4);
					if(s_urunID==eslesme){
						//DOSYADAN OKUNAN STRÝNG OLDUÐU ÝÇÝN CHAR TÝPÝNE DÖNÜÞÜMÜ BU ÞEKÝLDE SAÐLANIYOR
						//URUN_BÝLGÝ.TXT DEN URUN ID VE URUN ISMI ALINIYOR
						for(int i=0;i<34;i++){
							s_okunan+=idokunan[i];
						}
						onaylama=1;
					}
				}
				if(onaylama=0) cout << "GEÇERSÝZ ÜRÜN ID, TEKRAR DENEYÝNÝZ...";
			}while(onaylama=0);
			cout << "Sipariþ Edilen Ürünün Adedini Giriniz: "; cin >> s_urunADET; cin.ignore();
			cout << "Kargo Þirketini Giriniz: "; gets(k_sirketi); strupr(k_sirketi);
			//SÝPARÝÞ ID ATAMAK ÝÇÝN
			ifstream id_bak("siparis_bilgi.txt");
			int s_sayi=0;
			s2_urunADET=s_urunADET;
			while(!id_bak.eof()){
				s_sayi++;
				sayac++;
				getline(id_bak,idokunan);
				id_donustur=idokunan.substr(0,6);
				for(int i=0;i<6;i++){
					s_urunID[i]=id_donustur[i];
				}
				if(sayac==2){
				//DOSYA BOÞ ÝSE
					if(strlen(s_urunID)==0){
						dogruluk=1;
						
						siparis_bilgi << setw(15) << sip_id;
					}
				}
			}
			id_bak.close();
			int s_sayi2=0;
			ifstream id_bak2("siparis_bilgi.txt");
			//SIFIRLANDIÐI ÝÇÝN ATAMA YAPARAK KURTARDIM
			while(!id_bak2.eof()){
				s_sayi2++;
				getline(id_bak2,idokunan2);	
				if(s_sayi2==(s_sayi-1)){
					id_donustur=idokunan2.substr(0,6);
					for(int i=0;i<6;i++){
						s_urunID[i]=id_donustur[i];
					}
					idsayi2=atoi(s_urunID);
					if(dogruluk==0){
						siparis_bilgi << setw(15) << idsayi2+1;
					}
				}
			}
			id_bak2.close();
			siparis_bilgi << setw(42) << s_okunan << setw(12) << s2_urunADET << setw(12) << k_sirketi << endl;
			s_okunan="";
			siparis_bilgi.close();
			cout << "Sipariþ Baþarýyla Kaydedildi!\n";
	}
	void siparissorgu(){
		//SÝPARÝÞ SORGULAMA
		do{
			cout << "Siparis ID: "; cin >> s_urunID; cin.ignore();
			id_kontrol=strlen(s_urunID);
			if(id_kontrol!=6) cout << "Lütfen geçerli Siparis ID giriniz!\n";
		}while(id_kontrol!=6);
		//URUN DOSYADAN OKUNUYOR VE KONTROL ÝSLEMÝ YAPILIYOR
		ifstream sipid_oku("siparis_bilgi.txt");
		while(!sipid_oku.eof()){
			getline(sipid_oku,okunan);
			eslesme=okunan.substr(0,6);
			if (eslesme==s_urunID){
				cout.setf(ios::left);
				cout << endl << setw(15) << "SIPARIS ID" << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET"  << setw(12) << "KARGO S."<< endl;
				cout << okunan <<endl <<endl;
			}
		}
		sipid_oku.close();
	}
}urun2;

class islem:public hesap1,public hesap2{
};
int main(){
	char cevap;
	//ÜRÜN DEÐÝÞKENLERÝ
	char y_isim[30];
	char y_adet[5];
	int sayi_adet;
	setlocale(LC_ALL,"Turkish");
	int secim,secim2;
	int deger=0;
	int isim_kontrol;
	cout << "---SISTEME HOSGELDINIZ---\n\n";
	do{
	cout << "Hangi iþlemi yapmak istersiniz?\n1-Ürün Kayýt\n2-Ürünleri Listele\n3-Ürün Sorgu\n4-Ürün Silme\n5-Ürün Güncelleme\n6-Sipariþ Kayýt\n7-Sipariþ Sorgu\n";
	hesap1 hesap1();
	do{
		cout << "\nÝSLEM NO: "; cin >> secim;
		if(secim!=1 && secim!=2 && secim!=3 && secim!=4 && secim!=5 && secim!=6 && secim!=7) cout << "Lutfen dogru islem numarasi giriniz!";
	}while(secim!=1 && secim!=2 && secim!=3 && secim!=4 && secim!=5 && secim!=6 && secim!=7);
	cout << "\n";
	switch(secim){
		case 1:{
			//DIÞARIDAN ÜRÜN ÝSMÝ VE ADEDÝ ALINIYOR
			do{
				cout << "Ürün Ýsmi: "; cin.ignore(); gets(y_isim); strlwr(y_isim);
				if(y_isim=="") cout << "Lutfen isim alanýný boþ býrakmayýnýz..." << endl;
			}while(y_isim=="");
			
			do{
				do{
				cout << "(EN AZ 100 ADET)\nÜrün Adet: "; gets(y_adet);
				sayi_adet=atoi(y_adet);
				if(sayi_adet<100) cout << "Adet sayýnýz en az 100 olmalý!";
				}while(sayi_adet<100);
				if(y_adet=="") cout << "Lütfen adet alanýný boþ býrakmayýnýz..." << endl;
			}while(y_adet=="");
			
			urun.setisim(y_isim);
			urun.setadet(y_adet);
			urun.ekle();
			break;
		}
		case 2:{
			urun.listele();
			break;
		}
		case 3:{
			cout << "Arama iþlemini nasýl yapmak istersiniz?\n1-Ürün ID\n2-Ürün Ýsmi\n";
			cout << "ÝÞLEM NO:"; cin >> secim2; system("cls");
			
			urun.ara(secim2,isim_kontrol);
			break;
		}
		case 4:{
			urun2.sil();
			break;
		}
		case 5:{
			urun2.guncelle();
			break;
		}
		case 6:{
			urun2.setid2();
			urun2.sipariskayit(); 
			break;
		}
		case 7:{
			urun2.siparissorgu();
			break;
		}
	}
	int kontrol=0;
		do{
			cout << "Baþka iþlem yapmak istiyor musunuz?(E/H): "; 
			cin >> cevap;
			if(cevap=='e' || cevap=='E' || cevap=='h' || cevap=='H'){
				kontrol=0;
			}
			else{
				kontrol=1;
				system("cls"); 
				cout << "Gerçerli bir cevap giriniz!\n";	
			}
		}while(kontrol==1);
	system("cls");
	}while(cevap=='E' || cevap=='e');
	cout << "Çýkýþ yapýlýyor"; sleep(1); cout << "."; sleep(1); cout << "."; sleep(1); cout << ".";
	return 0;
	}
