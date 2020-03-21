#ifndef QMYTOOLBUTTON_H
#define QMYTOOLBUTTON_H

#include <QToolButton>

typedef enum{
    MenuType_None           = 0,
    MenuType_Zoom,
    MenuType_CamBtnSet,
    MenuType_Exit,
    Menutype_Show,
    Menutype_Brightness,
    MenuType_printNow,
    MenyType_Preset,
    MenuType_Video,
}emMenuType;


class QMyToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit QMyToolButton(QString qstrMin, QString qstrMax, QWidget *parent = nullptr, QString qstrTip="", int iType=MenuType_None);

    void    setSelect(bool bSelect);
    int     getType()
    {
        return m_iID;
    }

protected:
    virtual void    paintEvent(QPaintEvent *event);
    virtual void    mousePressEvent(QMouseEvent *e) override;

signals:
    void    clickBtn(QMyToolButton*);

public slots:
    void        onChangeBright(int iVal);

private:
    QPixmap             m_imgMin;
    QPixmap             m_imgMax;
    bool                m_bSelect       = false;
    QString             m_qstrTip;
    int                 m_iID           = MenuType_None;
};

#endif // QMYTOOLBUTTON_H
