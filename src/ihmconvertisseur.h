#ifndef IHMCONVERTISSEUR_H
#define IHMCONVERTISSEUR_H

#include <QtWidgets>

#define FARENHEIT 0
#define CELCIUS   1

class IHMConvertisseur : public QWidget
{
    Q_OBJECT

  public: // pour les tests
    QLineEdit*        valeurAConvertir;
    QLabel*           resultatConversion;
    QLabel*           uniteConversion;
    QComboBox*        choixConversion;
    QPushButton*      boutonConvertir;
    QPushButton*      boutonQuitter;
    QDoubleValidator* doubleValidator;
    int               choixConversionPrecedent;

  public:
    IHMConvertisseur(QWidget* parent = 0);
    ~IHMConvertisseur();
    void afficherUnite();
    void instancierWidgets();
    void initialiserWidgets();
    void positionnerWidgets();
    void connecterSignauxSlots();
    void initialiserFenetre();

  signals:
    void actualisation();

  public slots:
    void convertir();
    void permuter(int index);
};

#endif // IHMCONVERTISSEUR_H
