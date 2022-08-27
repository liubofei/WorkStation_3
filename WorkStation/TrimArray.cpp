#include "TrimArray.h"
#include <QGridLayout>
#include <QPushButton>

const QString Gree = "background-color:#00FF00";
const QString Whiter = "background-color:#FFFFFF";
const QString Red = "background-color:#FF0000";
const QString Blue = "background-color:#0000FF";
const QString Yellow = "background-color:#FFFF00";

TrimArray::TrimArray(QWidget *parent)
	: QWidget(parent)
{
	setRow(8);
	setCol(12);
	initData();
	initUi();
}

TrimArray::~TrimArray()
{
	for (int i = 0; i < m_row; ++i)
	{
		delete[] m_pButton[i];
	}
	delete[] m_pButton;
}

void TrimArray::setRow(unsigned short row)
{
	m_row = row;
}

void TrimArray::setCol(unsigned short col)
{
	m_col = col;
}

void TrimArray::resetUI()
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			QPalette pal = m_pButton[row][col].palette();
			QBrush brush = pal.base();
			QColor color = brush.color();

			int R, G, B;
			color.getRgb(&R, &G, &B);

			if (R == 0 && G == 255 && B == 0)
			{
				//ÂÌ
				m_pButton[row][col].setStyleSheet(Whiter);
			}

			if (R == 0 && G == 0 && B == 255)
			{
				//À¶
				m_pButton[row][col].setStyleSheet(Whiter);
			}
		}
	}
}

void TrimArray::setAllColor(QString color)
{
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			if (color=="Red")
			{
				m_pButton[row][col].setStyleSheet(Red);
			}
			else if (color == "Blue")
			{
				m_pButton[row][col].setStyleSheet(Blue);
			}
			else  if (color == "Whiter")
			{
				m_pButton[row][col].setStyleSheet(Whiter);
			}			
		}
	}
}

void TrimArray::btnClicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QString objText = btn->text();
	int id = objText.toInt();
	unsigned short row = 0;
	unsigned short col = 0;

	id2RowCol(id, row, col);

	QPalette pal = btn->palette();

	QBrush brush = pal.base();
	QColor color = brush.color();

	int R, G, B;
	color.getRgb(&R,&G,&B);

	if (R == 255 && G == 255 && B == 255)
	{
		//°×É«
		btn->setStyleSheet(Blue);
	}

	if (R == 255 && G == 0 && B == 0)
	{
		//ºì
		btn->setStyleSheet(Whiter);
	}

 	if (R == 0 && G == 255 && B == 0)
 	{
 		//ÂÌ		
 	}

	if (R == 0 && G == 0 && B == 255)
	{
		//À¶
		btn->setStyleSheet(Red);
	}
}

void TrimArray::onUpdateStatus(int row, int col, int status)
{
	QString color;
	if (status == 0){
		color = Whiter;
	}
	else if (status == 1){
		color = Blue;
	}
	else if (status == 2){
		color = Red;
	}
	else if (status == 3){
		color = Gree;
	}	
	m_pButton[row][col].setStyleSheet(color);
}

void TrimArray::onUpdateScanResult(int row, int col, bool status)
{
	int colId = row % 2 == 0 ? col : m_col - 1 - col;

	m_pButton[row][colId].setStyleSheet(status ? Gree : Red);
}

void TrimArray::onClearScanResult()
{
	setAllColor("Whiter");
}

void TrimArray::onUpdateOkTrayStatus(int row, int col)
{
	int colId = row % 2 == 0 ? col : m_col - 1 - col;
	m_pButton[row][colId].setStyleSheet(Whiter);
}

void TrimArray::onUpdateNgTrayStatus(int row, int col)
{
	int colId = row % 2 == 0 ? col : m_col - 1 - col;
	m_pButton[row][colId].setStyleSheet(Gree);
}

void TrimArray::onUpdateSortTrayStatus(int row, int col, int status)
{
	int colId = row % 2 == 0 ? col : m_col - 1 - col;
	m_pButton[row][colId].setStyleSheet(status == 0 ? Yellow : Blue);
}

void TrimArray::onInitSortTrayStatus(bool ** status)
{
	int colId = 0;
	for (int row = 0; row < m_row; ++row)
	{
		for (int col = 0; col < m_col; ++col)
		{
			colId = row % 2 == 0 ? col : m_col - 1 - col;
			m_pButton[row][colId].setStyleSheet(status[row][col] ? Gree : Red);
		}
	}
}

void TrimArray::onInitOkTrayStatus(bool ** status)
{
	int colId = 0;
	for (int row = 0; row < m_row; ++row)
	{
		for (int col = 0; col < m_col; ++col)
		{
			colId = row % 2 == 0 ? col : m_col - 1 - col;
			m_pButton[row][colId].setStyleSheet(status[row][col] ? Gree : Whiter);
		}
	}
}

void TrimArray::onInitNgTrayStatus()
{
	setAllColor("Whiter");
}

void TrimArray::initUi()
{
	int id = 1;
	QGridLayout *layout = new QGridLayout;
	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < m_col; col++)
		{
			m_pButton[row][col].setText(QString::number(id++));
			m_pButton[row][col].setStyleSheet(Whiter);
			m_pButton[row][col].setMinimumHeight(40);		
			int colId = row % 2 == 0 ? col : m_col - 1 - col;		
			layout->addWidget(&m_pButton[row][col], row, colId, 1, 1);
			//connect(&m_pButton[row][col], &QPushButton::clicked, this, &TrimArray::btnClicked);
		}
	}
	setLayout(layout);
}

void TrimArray::initData()
{
	m_pButton = new QPushButton*[m_row];
	for (int i = 0; i < m_row; ++i)
	{
		m_pButton[i] = new QPushButton[m_col];
	}
}

void TrimArray::id2RowCol(unsigned short id, unsigned short &row, unsigned short &col)
{
	int index = id - 1;
	row = index / m_col;
	int Oddeven = row % 2;
	int remainder = index % m_col;
	col = Oddeven == 0 ? remainder : m_col - 1 - remainder;
}
