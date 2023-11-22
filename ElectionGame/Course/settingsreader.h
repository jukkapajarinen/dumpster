#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H

#include <QRegularExpression>
#include <QString>

#include <map>

/**
 * @file
 * @brief Asetuksia lukeva singleton-luokka.
 */

namespace Interface
{

/**
 * @brief SettingsReader on singleton-luokka asetusten lukemiseen.
 *
 * Luokan kautta voidaan lukea merkkijonomuotoisia avain-arvopareja kiinteästi
 * määritellystä tiedostosta. Se ei sovellu hyvin monimutkaisemman datan
 * käsittelyyn. Asetukset luetaan tiedostosta laiskasti kun niitä ensimmäisen
 * kerran kysytään tai erikseen käskettäessä.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class SettingsReader
{
public:
    /**
     * @brief READER singleton-olio
     */
    static SettingsReader READER;

    /**
     * @brief purkaja
     */
    ~SettingsReader() = default;

    /**
     * @brief readSettings lukee pelin asetukset tiedostosta
     * @pre -
     * @post asetukset on luettu
     * @post Poikkeustakuu: perus
     * @exception FormatException asetustiedoston muoto on virheellinen
     * @exception IOException asetustiedostoa ei voitu avata luettavaksi
     */
    void readSettings();

    /**
     * @brief getValue antaa asetuksista avainta vastaavan arvon. Lukee asetukset, jos sitä ei ole ennestään tehty.
     * @pre -
     * @param key avain
     * @return avainta vastaava arvo
     * @post asetukset on luettu
     * @post Poikkeustakuu: perus
     * @exception FormatException asetustiedoston muoto on virheellinen (jos yritettiin lukea)
     * @exception IOException asetustiedostoa ei voitu avata luettavaksi (jos yritettiin lukea)
     * @exception KeyException tuntematon avain
     */
    QString getValue(QString key);

private:
    static const QString SETTINGS_PATH;
    static const QRegularExpression FORMAT;

    SettingsReader();

    SettingsReader(const SettingsReader&) = delete;
    SettingsReader& operator =(const SettingsReader&) = delete;

    bool read_;
    std::map<QString, QString> settings_;
};

} // Interface

#endif // SETTINGSREADER_H
