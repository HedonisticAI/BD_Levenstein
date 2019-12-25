//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>
#include <string>
#include <stdlib>
#pragma hdrstop

#include "Unit1.h"
#include "SecondUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	ADOQuery1->Connection=ADOConnection1;
	ADOQuery1->SQL->Add("SELECT body,id FROM public.dubl");
	ADOQuery1->DataSource=DataSource1;
	ADOQuery1->Active=true;
	ADOQuery1->ExecSQL();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int percent = atoi(AnsiString(Edit_Percent->Text).c_str()), is_unic = 1;
	string str,str_database, str_part, str_mem;
	String src, name;
	name = Edit_File_Name->Text;
	ifstream Main_File((Edit_File_Name->Text).c_str());
	if (!(Main_File.is_open())) {Label1->Caption = "Файл не открыт, проверьте правильность введённого имени.";} else{
		while(Main_File){
			Main_File >> str_part;
			str += " " + str_part;
		}
		str = reduce(str);
		ADOQuery1->Open();
		ADOQuery1->First();
		for(int i = 0; i<ADOQuery1->RecordCount; i++){
			src = ADOQuery1->FieldByName("body")->AsString;
			str_database=AnsiString(src).c_str();
			distanceString(str, str_database);
			if (!(((static_cast<double>(100 * (distanceString(str, str_database))))/static_cast<double>(count(str_database)))>(static_cast<double>(percent)))) is_unic = 0;
			ADOQuery1->Next();
		}
		if (is_unic) {Label1->Caption = "Текст уникален. Нажмите 'Добавить', чтобы добавить текст в базу данных";}
			else {Label1->Caption = "Текст не уникален. Нажмите 'Добавить', если всё равно хотите добавить текс в базу данных.";}
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	string str, str_part;
	String name;
	ifstream Main_File((Edit_File_Name->Text).c_str());
	while(Main_File){
		Main_File >> str_part;
		str += " " + str_part;
	}
	str = reduce(str);
	ADOQuery1->SQL->Text = UnicodeString("INSERT INTO public.dubl (body, id, name) VALUES ('") + str.c_str() + "'," + (ADOQuery1->RecordCount+1) + ",'" + AnsiString(name).c_str() + "');";
	ADOQuery1->ExecSQL();
	Label3->Caption = "Текст добавлен в базу данных.";
}
//---------------------------------------------------------------------------

