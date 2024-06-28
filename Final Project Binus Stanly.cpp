#include<iostream>
#include<vector>
#include<string>

using namespace std;

class produk {
	protected:
		string kodeproduk;
		string namaproduk;
	public:
		produk(string kode="" , string nama="") : kodeproduk(kode) , namaproduk(nama) {}
		
		string getkodeproduk () const {return kodeproduk;}
		string getnamaproduk () const {return namaproduk;}
		
		void setnamaproduk(const string& nama) {namaproduk=nama;}
		
		virtual void display() const {
			cout << "Kode Produk :" << kodeproduk << ", Nama Produk :" << namaproduk;
		}
		
		virtual ~produk() {}
}; 

class botolminum : public produk {
	protected:
		float volume;
	public:
		botolminum(string kode="" , string nama="" , float v=0.0) : produk(kode,nama) , volume(v) {}
		
		float getvolume () const { return volume;}
		void setvolume(float vol) {volume=vol;}
		
		void display() const override {
			produk::display();
			cout << ", Volume :" << volume << "ml"<< endl;
		}
};

class mouse : public produk {
	protected:
		int baterai;
	public:
		mouse(string kode="", string nama="",int bat=0) : produk(kode,nama) ,baterai(bat) {}
		
		int getbaterai() const {return baterai;}
		void setbaterai(int bat) {baterai=bat;}
		
		void display() const override{
			produk::display();
			cout << ", Baterai :" << baterai << " Jam"<<endl;
		}
};

class kotakpensil : public produk{
	protected:
		int kompartemen;
	public:
		kotakpensil(string kode="", string nama="",int komp=0) : produk(kode,nama), kompartemen(komp) {}
		
		int getkompartemen() const {return kompartemen;}
		void setkompartemen(int komp) {kompartemen=komp;}
		
		void display() const override {
			produk::display();
			cout << ", Kompartemen:" << kompartemen << endl;
		}
};

produk* cariprodukbykode(const vector<produk*>& container, const string& kode){
	for(auto& produk:container) {
		if(produk->getkodeproduk() == kode){
			return produk;
		}
	}
	return nullptr;
}

bool deleteprodukbykode(vector<produk*>& container,const string& kode) {
	for(auto i=container.begin();i !=container.end();i++){
		if((*i)->getkodeproduk()==kode){
			delete *i;
			container.erase(i);
			return true;
		}
	}
	return false;
}

int main(){
	vector<produk*>container;
	
	bool isrunning = true;
	int pilihan;
	
	while (isrunning){
		cout << "1. Add Product"<<endl;
		cout << "2. Edit Product"<<endl;
		cout << "3. Display All Product"<<endl;
		cout << "4. Display Product By ID"<<endl;
		cout << "5. Delete All Product"<<endl;
		cout << "6. Delete Product By ID"<<endl;
		cout << "0. Exit Program"<<endl;
		
		cout << "Input Pilihan: ";cin>>pilihan;
		
		if(pilihan==1){
			string kode,nama;
			int jenisproduk;
			cout << "Masukan Kode Produk:";cin>>kode;
			if (cariprodukbykode(container, kode) !=nullptr){
				cout << "Kode Produk Sudah dipakai" <<endl;
				continue;
			}
			cout << "Masukan Nama Produk: ";cin >> nama;
			cout << "Masukan Jenis Produk(1 Botol Minum,2 Mouse, 3 Kotak Pensil): ";cin>>jenisproduk;
			
			if(jenisproduk==1){
				float volume;
				cout << "Masukan Volume(ml): ";cin>> volume;
				container.push_back(new botolminum(kode,nama,volume));
			}else if(jenisproduk==2){
				int baterai;
				cout << "Masukan battery life (jam): ";cin>>baterai;
				container.push_back(new mouse(kode,nama,baterai));
			}else if(jenisproduk==3){
				int kompartemen;
				cout << "Masukan jumlah kompartemen: ";cin >> kompartemen;
				container.push_back(new kotakpensil(kode,nama,kompartemen));
			}else{
				cout<<"Invalid Kode Produk" << endl;
			}
		}else if(pilihan==2){
			string kode,nama;
			cout << "Masukan Kode Produk to Edit: "; cin >> kode;
			
			produk*produk= cariprodukbykode(container, kode);
			if(produk==nullptr) {
				cout<< "Produk Tidak ditemukan"<<endl;
				continue;
			}
			
			cout << "Masukan Nama Produk Baru: ";cin>>nama;
			produk->setnamaproduk(nama);
			
			if(botolminum*botol = dynamic_cast<botolminum*>(produk)){
				float volume;
				cout << "Masukan Volume(ml): ";cin >> volume;
				botol->setvolume(volume);
			}else if(mouse*Mouse=dynamic_cast<mouse*>(produk)){
				int baterai;
                cout << "Masukan Baterai Baru (jam): "; cin >> baterai;
                Mouse->setbaterai(baterai);
			}
		}else if(pilihan==3) {
			for(const auto& produk : container){
				produk->display();
			}
		}else if(pilihan==4) {
			string kode;
			cout<< "Masukan Kode Produk: ";cin>>kode;
			
			produk*produk=cariprodukbykode(container, kode);
			if(produk !=nullptr){
				produk->display();
			}else{
				cout<<"Produk Tidak Ditemukan!"<<endl;
			}
		}else if(pilihan==5){
			for(auto& Produk : container){
				delete Produk;
			}
			container.clear();
			cout<<"Semua Produk Terhapus"<<endl;
		}else if(pilihan==6){
			string kode;
			cout<<"Masukan Kode Produk: ";cin>> kode;
			
			if (deleteprodukbykode(container, kode)){
				cout<<"Produk terhapus" << endl;
			}else{
				cout<<"Produk Tidak ditemukan"<<endl;
			}
		}else{
			isrunning=false;
		}
	}
		
	for (auto& produk : container) {
	    delete produk;
    }
    return 0;
}
