#include <QContextMenuEvent>
#include <QFileDialog>
#include <QInputDialog>

#include "medialist.h"

#pragma execution_character_set("utf-8")

MediaList::MediaList(QWidget *parent)
    : QListWidget(parent),
    m_stMenu(this)
{



}

MediaList::~MediaList()
{
}

bool MediaList::Init()
{
    m_stActAdd.setText("添加文件");
    m_stMenu.addAction(&m_stActAdd);
	m_stActAddStream.setText("添加流媒体");
	m_stMenu.addAction(&m_stActAddStream);
    m_stActRemove.setText("移除所选项");
    QMenu* stRemoveMenu = m_stMenu.addMenu("移除");
    stRemoveMenu->addAction(&m_stActRemove);
    m_stActClearList.setText("清空列表");
    m_stMenu.addAction(&m_stActClearList);


	connect(&m_stActAdd, &QAction::triggered, this, &MediaList::AddFile);
	connect(&m_stActAddStream, &QAction::triggered, this, &MediaList::AddStream);
	connect(&m_stActRemove, &QAction::triggered, this, &MediaList::RemoveFile);
    connect(&m_stActClearList, &QAction::triggered, this, &QListWidget::clear);

    return true;
}

void MediaList::contextMenuEvent(QContextMenuEvent* event)
{
    m_stMenu.exec(event->globalPos());
}

void MediaList::AddFile()
{
#if 1
    //QList<QUrl> QFileDialog::getOpenFileUrls
    QStringList listFileName = QFileDialog::getOpenFileNames(this, "打开文件", QDir::homePath(),
        "视频文件(*.mkv *.rmvb *.mp4 *.avi *.flv *.wmv *.3gp)");

    for (QString strFileName : listFileName)
    {
        emit SigAddFile(strFileName);
    }
#endif
	// QString strFileName = "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov";
	// QString strFileName = "D:/Work/Dev/Material/Video\\4K_3412x1920-27mb.mp4";
	// emit SigAddFile(strFileName);
}

void MediaList::RemoveFile()
{
    takeItem(currentRow());
}

void MediaList::AddStream()
{
#if 0
	//QList<QUrl> QFileDialog::getOpenFileUrls
	QStringList listFileName = QFileDialog::getOpenFileNames(this, "打开文件", QDir::homePath(),
		"视频文件(*.mkv *.rmvb *.mp4 *.avi *.flv *.wmv *.3gp)");

	for (QString strFileName : listFileName)
	{
		emit SigAddFile(strFileName);
	}
#endif
	bool ok;
	QString text = QInputDialog::getText(this, tr("添加流媒体地址到播放列表"),
		tr("请输入流媒体地址:"), QLineEdit::Normal,
		tr("rtsp://***"), &ok);

	if (ok && !text.isEmpty())
		emit SigAddFile(text);

	// QString strFileName = "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov";
	// QString strFileName = "D:/Work/Dev/Material/Video\\4K_3412x1920-27mb.mp4";
	// emit SigAddFile(strFileName);
}


