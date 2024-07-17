#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 100

// Cau truc mot cuon sach:
struct QuanLySach
{
	char MaSach[MAXSIZE], TenSach[MAXSIZE], TacGia[MAXSIZE], NhaXuatBan[MAXSIZE], TheLoai[MAXSIZE];
	int NamXuatBan;
};

// Cau truc cua nguoi muon sach
struct NguoiDocGia
{
	char MaDocGia[MAXSIZE], TenSachMuon[MAXSIZE];
};

// cau truc node 
struct Node
{
	QuanLySach data;
	NguoiDocGia dg;
	Node *pNext;
	Node *pPrev;
};

// khai bao cau truc double list
struct DList
{
	Node *pHead;
	Node *pTail;
};

// ham khoi tao node
Node *KhoiTaoNode(QuanLySach x)
{
	Node *p = new Node;
	p->data = x;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
}

// ham khoi tao node DANH SCHO NGUOI MUON SACH
Node *KhoiTaoNode_NguoiDocGia(NguoiDocGia x)
{
	Node *p = new Node;
	p->dg = x;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
}

// ham khoi tao double list
void KhoiTaoDList(DList &dl)
{
	dl.pHead = dl.pTail = NULL;
}

// kiem tra danh sach rong
int KiemTraRong(DList dl)
{
	if (dl.pHead == NULL)
	{
		return 1;
	}
	return 0;
}

// Ham dem so phan tu
int DemSoPhanTu(DList dl)
{
	int dem=0;
	for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
	{
		dem++;
	}
	return dem;
}
//=======================================THEM PHAN TU=======================================\\

// them node vao dau danh sach
void ThemVaoDau(DList &dl, Node *p)
{
	if (KiemTraRong(dl)==1)
	{
		dl.pHead = dl.pTail = p;
	}
	else
	{
		p->pNext = dl.pHead;
		dl.pHead->pPrev = p;
		dl.pHead = p;
	}
}

// them node vao cuoi danh sach
void ThemVaoCuoi(DList &dl, Node *p)
{
	if (KiemTraRong(dl)==1)
	{
		dl.pHead = dl.pTail = p;
	}
	else
	{
		dl.pTail->pNext = p;
		p->pPrev = dl.pTail;
		dl.pTail = p;
	}
}

// them phan tu vao vi tri bat ky trong danh sach
void ThemBatKy(DList &dl, Node *p, int vitri)
{
	int n = DemSoPhanTu(dl);
	if (vitri <= 1 || KiemTraRong(dl)==1)
	{
		ThemVaoDau(dl,p);
	}
	else if (vitri > n)
	{
		ThemVaoCuoi(dl,p);
	}
	else
	{
		int dem=0;
		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			dem++;
			Node *g = k->pPrev;
			if (vitri == dem)
			{
				p->pNext = k;
				k->pPrev = p;
				g->pNext = p;
				p->pPrev = g;
				break;
			}
		}
	}
}

//=======================================XOA PHAN TU=======================================\\

// xoa dau
void XoaDau(DList &dl, QuanLySach &x)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
	}
	else
	{
		x = dl.pHead->data;
		Node *p = dl.pHead;
		dl.pHead = dl.pHead->pNext;
		delete p;
	}
}

// xoa cuoi
void XoaCuoi(DList &dl, QuanLySach &x)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
	}
	else if (dl.pHead->pNext==NULL)
	{
		XoaDau(dl,x);
	}
	else
	{
		x = dl.pTail->data;
		for (Node *k = dl.pHead; k != NULL; k = k->pNext)
		{
			if (k->pNext == dl.pTail)
			{
				delete dl.pTail;
				dl.pTail = k;
				k->pNext = NULL;
			}
		}
	}
}

// xoa phan tu bat ky
void XoaBatKy(DList &dl, int vitri, QuanLySach &x)
{
	int n = DemSoPhanTu(dl);
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
	}
	else if (vitri <= 1)
	{
		XoaDau(dl,x);
	}
	else if (vitri >= n)
	{
		XoaCuoi(dl,x);
	}
	else
	{
		Node *h;
		int dem=0;
		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			dem++;
			Node *g = k->pPrev;
			if (vitri == dem)
			{
				x = k->data;
				h=k->pNext;
				g->pNext = h;
				h->pPrev = g;
				delete k;
				return;
			}
		}
	}
}

// xuat ra mot node
void xuat_MotNode(Node *k)
{
	printf("Ma Sach:%s\n", k->data.MaSach);
	printf("Ten Cuon Sach:%s\n", k->data.TenSach);
	printf("Tac Gia:%s\n", k->data.TacGia);
	printf("Nhap nha xuat ban:%s\n", k->data.NhaXuatBan);
	printf("Nam Xuat Ban:%d\n", k->data.NamXuatBan);
	printf("The loai:%s\n", k->data.TheLoai);
	printf("\n");
}

// duyet danh sach
void DuyetDanhSach(DList dl)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
	}
	else
	{
		int i=1;
		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			printf("VI VRI:%d\n", i);
			xuat_MotNode(k);
			i++;
		}
	}
}

//===================================================================================\\

// Ham Nhap thong tin mot cuon sach
void NhapSach(QuanLySach &x)
{
	printf("Nhap Ma Sach:"); getchar(); gets(x.MaSach);
	printf("Nhap Ten Sach:"); gets(x.TenSach);
	printf("Nhap Ten Tac gia:"); gets(x.TacGia);
	printf("Nhap nha xuat ban:"); gets(x.NhaXuatBan);
	printf("Nhap nam xuat ban:"); scanf("%d", &x.NamXuatBan);
	printf("Nhap the loai:"); getchar(); gets(x.TheLoai);
}

// Swap
void swap(Node *a, Node *b)
{
	QuanLySach temp;
	temp=a->data;
	a->data=b->data;
	b->data=temp;
}
// Ham sap xep sach theo the loai, trong tung the loai thi sap xep theo ma sach
void SapXepSach(DList dl)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
	}
	else
	{
		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			for (Node *h=k->pNext; h!=NULL; h=h->pNext)
			{
				if (strcmpi(k->data.TheLoai,h->data.TheLoai)==0)
				{
					if (strcmpi(k->data.MaSach, h->data.MaSach) > 0) 
					{
						swap(k,h);
					}
				}
				else if (strcmpi(k->data.TheLoai,h->data.TheLoai) > 0)
				{
					swap(k,h);
				}
			}
		}
	}
}

// Ham tim tac gia co nhieu sach nhat
void TimTG_CoNhieuSachNhat(DList dl)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
		printf("Hoac khong co Tac Gia nao nhieu sach nhat\n");
	}
	else
	{
		int max=0;
		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			int dem=0;
			for (Node *h=k->pNext; h!=NULL; h=h->pNext)
			{
				if (strcmpi(k->data.TacGia,h->data.TacGia)==0)
				{
					dem++;
				}
			}
			if (dem >= max)
			{
				max = dem;
			}
		}

		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			int dem1=0;
			for (Node *h=k->pNext; h!=NULL; h=h->pNext)
			{
				if (strcmpi(k->data.TacGia,h->data.TacGia)==0)
				{
					dem1++;
				}
			}
			if (dem1==max)
			{
				printf("Tac gia co nhieu sach nhat:%s\n", k->data.TacGia);
			}
		}
	}	
}

// Ham tim nha xuat ban co it sach nhat
void TimNXB_CoItSachNhat(DList dl)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
		printf("Hoac khong co NXB nao it sach nhat\n");
	}
	else
	{
		int min=MAXSIZE;
		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			int dem=0;
			for	(Node *h=dl.pHead; h!=NULL; h=h->pNext)
			{
				if (strcmpi(k->data.NhaXuatBan,h->data.NhaXuatBan)==0)
				{
					dem++;
				}
			}
			if (dem <= min)
			{
				min = dem;
			}	
		}

		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			int dem1=0;
			for (Node *h=dl.pHead; h!=NULL; h=h->pNext)
			{
				if (strcmpi(k->data.NhaXuatBan,h->data.NhaXuatBan)==0)
				{
					dem1++;
				}
			}
			if (dem1==min)
			{
				printf("NXB co it sach nhat:%s\n", k->data.NhaXuatBan);
			}
		}

	}	
}

// Ham thong ke sach theo tung nam xuat ban
void ThongKeSachTheoNam(DList dl)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
	}
	else
	{
		const int MAX_NAM = 10000;
		int dem[MAX_NAM]={ 0 };
		for (Node* k = dl.pHead; k != NULL; k = k->pNext)
		{
			int Nam = k->data.NamXuatBan;
			dem[Nam]++;
		}
		for (int Nam = 0; Nam < MAX_NAM; Nam++)
		{
			if (dem[Nam] > 0)
			{
				printf("Sach xuat ban trong nam %d: %d\n", Nam, dem[Nam]);
			}
		}
	}
}

// Ham dem so luong sach theo tung the loai
void SoLuongSachTheoTheLoai(DList dl)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Danh sach rong!!!\n");
	}
	else
	{
		char arrTheLoai[10][50];
		int dem[10];
		int i = 0;
		for (Node *k=dl.pHead; k!=NULL; k=k->pNext)
		{
			int j=0;
			while (j<i && strcmpi(arrTheLoai[j], k->data.TheLoai) != 0)
			{
				j++;
			}
			if (j==i)
			{
				int count=0;
				for (Node *h=dl.pHead; h!=NULL; h=h->pNext)
				{
					if (strcmpi(k->data.TheLoai,h->data.TheLoai)==0)
					{
						count++;
					}
				}
				strcpy(arrTheLoai[i], k->data.TheLoai);
				dem[i] = count;
				i++;
			}
		}
		for (int j = 0; j < i; j++)
		{
			printf("Sach the loai %s: %d\n", arrTheLoai[j], dem[j]);
		}
	}
}

// Ham tim kiem sach theo ten, ma sach, the loai, tac gia, nam xuat ban, nha xuat ban
void TimKiemSach(DList dl)
{
	char TuKhoa[MAXSIZE];
	int t=0;
	printf("Nhap tu khoa can tim:");
	getchar();
	gets(TuKhoa);
	int a = atoi(TuKhoa);
	for (Node *k=dl.pHead; k!=NULL ; k=k->pNext)
	{
		if (strcmpi(TuKhoa,k->data.TenSach)==0 || strcmpi(TuKhoa,k->data.MaSach)==0 || strcmpi(TuKhoa,k->data.NhaXuatBan)==0 || strcmpi(TuKhoa,k->data.TacGia)==0 || strcmpi(TuKhoa,k->data.TheLoai)==0)
		{
			xuat_MotNode(k);
			t++;
		}
		else if (a==k->data.NamXuatBan)
		{
			xuat_MotNode(k);
			t++;
		}
	}

	if (t==0)
	{
		printf("Khong tim thay thong tin sach!!!\n");
	}
}

// Ham muon sach
void MuonSach(DList &dl, DList &sdl, DList &Luu_NguoiDocGia, QuanLySach &x)
{
	if (KiemTraRong(dl)==1)
	{
		printf("Thu vien dang rong, khong the cho muon!!!\n");
	}
	else
	{
		NguoiDocGia a;
		printf("Nhap ma doc gia:");
		getchar(); gets(a.MaDocGia);
		printf("Nhap ten cuoi sach can muon:");
		gets(a.TenSachMuon);
		int vitri=0;
		for (Node *k = dl.pHead; k !=NULL ; k=k->pNext)
		{
			vitri++;
			if (strcmpi(a.TenSachMuon,k->data.TenSach)==0)
			{
				Node *q=KhoiTaoNode_NguoiDocGia(a);
				ThemVaoCuoi(Luu_NguoiDocGia,q);
				XoaBatKy(dl,vitri,x);
				Node *p = KhoiTaoNode(x);
				ThemVaoCuoi(sdl,p);
				printf("Muon thanh cong!!!\n");
				printf("\n");
				return;
			}
		}
		printf("Khong co cuon sach nao co ten %s", a.TenSachMuon);
	}
}

// Ham duyet danh sach ma doc gia
void DuyetDS_MaDocGia(DList Lua_NguoiDocGia)
{
	for (Node *k=Lua_NguoiDocGia.pHead ; k!=NULL ; k=k->pNext)
	{
		printf("Ma Doc Gia:%s - Ten Cuon Sach:%s\n", k->dg.MaDocGia, k->dg.TenSachMuon);
	}
}

// Ham Tra Sach
void TraSach(DList &dl, DList &sdl, DList &Luu_NguoiDocGia, QuanLySach &x)
{
	NguoiDocGia ss;
	printf("Nhap Ma Doc Gia can tra:");
	getchar(); gets(ss.MaDocGia);
	printf("Nhap ten cuon sach can tra:");
	gets(ss.TenSachMuon);
	int vitri=0;
	for (Node *k=Luu_NguoiDocGia.pHead; k!=NULL; k=k->pNext)
	{
		vitri++;
		if (strcmpi(ss.MaDocGia,k->dg.MaDocGia)==0 && strcmpi(ss.TenSachMuon,k->dg.TenSachMuon)==0)
		{
			QuanLySach b;
			XoaBatKy(Luu_NguoiDocGia,vitri,b);
			XoaBatKy(sdl,vitri,x);
			Node *p = KhoiTaoNode(x);
			ThemVaoCuoi(dl,p);
			printf("Tra sach thanh cong!!!\n");
			return;
		}
	}
	printf("Khong tim thay ma doc gia!!!\n");
	printf("Hoac Khong tim thay ten cuon sach!!!\n");
}

// ham chinh
int main()
{
	DList dl;
	DList sdl;
	DList Luu_NguoiDocGia;
	QuanLySach x;
	int y;
	KhoiTaoDList(dl);
	KhoiTaoDList(sdl);
	KhoiTaoDList(Luu_NguoiDocGia);
	printf("<<===========================Ung Dung Quan Ly Sach Trong Thu Vien===========================>>\n\n");
	printf("Vui long nhan Enter de tiep tuc...\n");
	getch();
	char luachon[50];
	do
	{
		printf("===========================\n");
		printf("1. Them Sach vao thu vien\n");
		printf("2. Xoa Sach ra khoi thu vien\n");
		printf("3. Sap Xep sach theo the loai, trong tung the loai thi sap xep theo ma sach\n");
		printf("4. Tim tac gia co nhieu sach nhat\n");
		printf("5. Tim nha xuat ban co it sach nhat\n");
		printf("6. Thong ke sach theo tung nam xuat ban\n");
		printf("7. Dem so luong sach theo tung the loai\n");
		printf("8. Tim kiem sach(theo ten, ma sach, the loai, tac gia, nha xuat ban, nam xuat ban)\n");
		printf("9. Quan ly tra, muon sach\n");
		printf("10. Duyet Danh Sach!!!\n");
		printf("0. Thoat!!!\n");
		printf("===========================\n");
		printf("Lua chon cua ban:");
		scanf(" %s", &luachon);
		printf("\n");
		if (strcmpi(luachon,"1")==0)
		{
			char a;
			do
			{
				printf("-----------------------------\n");
				printf("-1. Them vao dau\n");
				printf("-2. Them vao cuoi\n");
				printf("-3. Them vao vi tri bat ky\n");
				printf("-4. Duyet danh sach\n");
				printf("-0. Quay Lai!!!\n");
				printf("-----------------------------\n");
				printf("Lua chon cua ban:");
				scanf(" %c", &a);
				printf("\n");
				if (a=='1')
				{
					NhapSach(x);
					Node *p = KhoiTaoNode(x);
					ThemVaoDau(dl,p);
					printf("\n");
				}
				else if (a=='2')
				{
					NhapSach(x);
					Node *p = KhoiTaoNode(x);
					ThemVaoCuoi(dl,p);
					printf("\n");
				}
				else if (a=='3')
				{
					if (KiemTraRong(dl)==1)
					{
						printf("Hien tai ke sach dang rong nen se mac dinh cho vao tri vi dau tien!!!\n");
						NhapSach(x);
						Node *p = KhoiTaoNode(x);
						ThemVaoCuoi(dl,p);
						printf("\n");
					}
					else
					{
						int vitri;
						printf("Nhap vitri:");
						scanf("%d", &vitri);
						NhapSach(x);
						Node *p = KhoiTaoNode(x);
						ThemBatKy(dl,p,vitri);
						printf("\n");
					}
				}
				else if (a=='4')
				{
					DuyetDanhSach(dl);
					printf("\n");
				}
			} while (a!='0');
		}
		else if (strcmpi(luachon,"2")==0)
		{
			char a;
			do
			{
				printf("-----------------------------\n");
				printf("-1. Xoa Dau\n");
				printf("-2. Xoa Cuoi\n");
				printf("-3. Xoa vi tri bat ky\n");
				printf("-4. Duyet danh sach\n");
				printf("-0. Quay Lai!!!\n");
				printf("-----------------------------\n");
				printf("Lua chon cua ban:");
				scanf(" %c", &a);
				printf("\n");
				if (a=='1')
				{
					XoaDau(dl,x);
					printf("\n");
				}
				else if (a=='2')
				{
					XoaCuoi(dl,x);
					printf("\n");
				}
				else if (a=='3')
				{
					int vitri;
					printf("Nhap vi tri cuon sach muon xoa:");
					scanf("%d", &vitri);
					XoaBatKy(dl,vitri,x);
				}
				else if (a=='4')
				{
					DuyetDanhSach(dl);
					printf("\n");
				}
			} while (a!='0');
		}
		else if (strcmpi(luachon,"3")==0)
		{
			SapXepSach(dl);
			DuyetDanhSach(dl);
			printf("\n");
		}
		else if (strcmpi(luachon,"4")==0)
		{
			TimTG_CoNhieuSachNhat(dl);
			printf("\n");
		}
		else if (strcmpi(luachon,"5")==0)
		{
			TimNXB_CoItSachNhat(dl);
			printf("\n");
		}
		else if (strcmpi(luachon,"6")==0)
		{
			ThongKeSachTheoNam(dl);
			printf("\n");
		}
		else if (strcmpi(luachon,"7")==0)
		{
			SoLuongSachTheoTheLoai(dl);
			printf("\n");
		}
		else if (strcmpi(luachon,"8")==0)
		{
			TimKiemSach(dl);
			printf("\n");
		}
		else if (strcmpi(luachon,"9")==0)
		{		
			char a;
			do
			{
				printf("-----------------------------\n");
				printf("-1. Muon Sach\n");
				printf("-2. Danh sach cac doc gia dang muon sach\n");
				printf("-3. Tra Sach\n");
				printf("-0. Quay Lai!!!\n");
				printf("-----------------------------\n");
				printf("Lua chon cua ban:");
				scanf(" %c", &a);
				printf("\n");
				if (a=='1')
				{
					MuonSach(dl, sdl, Luu_NguoiDocGia,x);
					printf("\n");
				}
				else if (a=='2')
				{
					printf("==DANH SACH MA DOC GIA==\n");
					DuyetDS_MaDocGia(Luu_NguoiDocGia);
					printf("\n");
				}
				else if (a=='3')
				{
					TraSach(dl, sdl, Luu_NguoiDocGia, x);
					printf("\n");
				}
			} while (a!='0');
		}
		else if (strcmpi(luachon,"10")==0)
		{
			DuyetDanhSach(dl);
			printf("\n");
		}
	} while (strcmpi(luachon,"0")!=0);
	getch();
	return 0;
}