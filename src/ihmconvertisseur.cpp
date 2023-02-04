#include "ihmconvertisseur.h"

IHMConvertisseur::IHMConvertisseur(QWidget* parent) : QWidget(parent)
{
    instancierWidgets();

    initialiserWidgets();

    positionnerWidgets();

    connecterSignauxSlots();

    initialiserFenetre();
}

IHMConvertisseur::~IHMConvertisseur()
{
}

void IHMConvertisseur::convertir()
{
    if(valeurAConvertir->text().isEmpty())
    {
        resultatConversion->setText(QString::fromUtf8("--.--"));
        afficherUnite();
        return;
    }
    int               position   = 0;
    QString           valeur     = valeurAConvertir->text();
    QValidator::State validation = doubleValidator->validate(valeur, position);
    if(validation == QValidator::Invalid)
    {
        valeurAConvertir->clear();
        resultatConversion->setText(QString::fromUtf8("--.--"));
    }
    else
    {
        switch(choixConversion->currentIndex())
        {
            case FARENHEIT:
                resultatConversion->setText(QString::fromUtf8("%1").arg(
                  9 * valeurAConvertir->text().toDouble() / 5 + 32,
                  0,
                  'f',
                  2));
                break;
            case CELCIUS:
                resultatConversion->setText(QString::fromUtf8("%1").arg(
                  5 * (valeurAConvertir->text().toDouble() - 32) / 9,
                  0,
                  'f',
                  2));
                break;
        }
    }
    afficherUnite();
}

void IHMConvertisseur::permuter(int index)
{
    bool estImpair = (index % 2);
    /* est-ce une permutation ? */
    if((estImpair && index - 1 == choixConversionPrecedent) ||
       (!estImpair && index + 1 == choixConversionPrecedent))
    {
        if(resultatConversion->text() != "--.--")
        {
            valeurAConvertir->setText(resultatConversion->text());
        }
    }
    emit actualisation();
    afficherUnite();
    choixConversionPrecedent = index;
    valeurAConvertir->setFocus();
}

void IHMConvertisseur::afficherUnite()
{
    switch(choixConversion->currentIndex())
    {
        case FARENHEIT:
            uniteConversion->setText(QString::fromUtf8(" °F"));
            break;
        case CELCIUS:
            uniteConversion->setText(QString::fromUtf8(" °C"));
            break;
    }
}

void IHMConvertisseur::instancierWidgets()
{
    valeurAConvertir   = new QLineEdit(this);
    resultatConversion = new QLabel(this);
    uniteConversion    = new QLabel(this);
    choixConversion    = new QComboBox(this);
    boutonConvertir    = new QPushButton(QString::fromUtf8("Convertir"), this);
    boutonQuitter      = new QPushButton(QString::fromUtf8("Quitter"), this);
    doubleValidator    = new QDoubleValidator(this);
}

void IHMConvertisseur::initialiserWidgets()
{
    valeurAConvertir->clear();
    resultatConversion->setText("--.--");
    uniteConversion->setText(QString::fromUtf8(" °F"));
    choixConversion->addItem("Celcius -> Farenheit");
    choixConversion->addItem("Farenheit -> Celcius");
    choixConversion->setCurrentIndex(FARENHEIT);
    choixConversionPrecedent = choixConversion->currentIndex();
    doubleValidator->setLocale(QLocale::C); // problème point et virgule !
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setDecimals(2);
    valeurAConvertir->setValidator(doubleValidator);
}

void IHMConvertisseur::positionnerWidgets()
{
    QHBoxLayout* hLayoutConversion = new QHBoxLayout;
    QHBoxLayout* hLayoutBoutons    = new QHBoxLayout;
    QVBoxLayout* vLayoutPrincipal  = new QVBoxLayout;
    hLayoutConversion->addWidget(valeurAConvertir);
    hLayoutConversion->addWidget(choixConversion);
    hLayoutConversion->addWidget(resultatConversion);
    hLayoutConversion->addWidget(uniteConversion);
    hLayoutBoutons->addWidget(boutonConvertir);
    hLayoutBoutons->addWidget(boutonQuitter);
    vLayoutPrincipal->addLayout(hLayoutConversion);
    vLayoutPrincipal->addLayout(hLayoutBoutons);
    setLayout(vLayoutPrincipal);
}

void IHMConvertisseur::connecterSignauxSlots()
{
    connect(choixConversion,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(permuter(int)));
    connect(this, SIGNAL(actualisation()), this, SLOT(convertir()));
    // Conversion manuelle
    connect(boutonConvertir, SIGNAL(clicked()), this, SLOT(convertir()));
    connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    // Conversion automatique
    /*connect(valeurAConvertir, SIGNAL(textChanged(QString)), this,
     * SLOT(convertir()));*/
}

void IHMConvertisseur::initialiserFenetre()
{
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    minimumSizeHint(),
                                    qApp->desktop()->availableGeometry()));
    setWindowTitle("Conversion d'unités marines");
    valeurAConvertir->setFocus();
}
