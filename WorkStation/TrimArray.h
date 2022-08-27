#pragma once
#include <QtWidgets/QWidget>

class QPushButton;


class TrimArray : public QWidget
{
	Q_OBJECT

public:
	TrimArray(QWidget *parent = Q_NULLPTR);
	~TrimArray();
	void setRow(unsigned short row);
	void setCol(unsigned short col);
	void resetUI();
	void setAllColor(QString color);


public slots :
	void btnClicked();
	void onUpdateStatus(int row, int col, int status);

	//scan
	void onUpdateScanResult(int row, int col, bool status);
	void onClearScanResult();


	/*
	ok�� ���� ��ɫ
		 ���� ��ɫ

	ng�� ���� ��ɫ
		 ���� ��ɫ

	������ OK��  ��ɫ
			ng�� ��ɫ
			��ȡNg�� ��ɫ
			�ѷ�OK��  ��ɫ
	*/
	//sort
	void onUpdateOkTrayStatus(int row, int col);
	void onUpdateNgTrayStatus(int row, int col);
	void onUpdateSortTrayStatus(int row, int col, int status);
	void onInitSortTrayStatus(bool ** status);
	void onInitOkTrayStatus(bool ** status);
	void onInitNgTrayStatus();
	

private:
	void initUi();
	void initData();
	void id2RowCol(unsigned short id, unsigned short &row, unsigned short &col);

private:
	unsigned short m_row;
	unsigned short m_col;
	QPushButton** m_pButton;
};
