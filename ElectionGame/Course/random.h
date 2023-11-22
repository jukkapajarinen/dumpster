#ifndef RANDOM_H
#define RANDOM_H

#include <random>

/**
 * @file
 * @brief Satunnaislukuja tuottava singleton-luokka.
 */

namespace Interface
{

/**
 * @brief Random on singleton-luokka satunnaislukujen tuottamiseen.
 *
 * Kaikki pelissä käytettävät satunnaisluvut pitäisi tuottaa tämän luokan
 * kautta, jottei rinnakkaisten generaattorien käyttö pääse rikkomaan lukujen
 * ennustamattomuutta.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class Random
{
public:
    /**
     * @brief RANDOM singleton-olio
     */
	static Random RANDOM;

    /**
     * @brief purkaja
     */
	~Random() = default;

    /**
     * @brief uint tuottaa satunnaisen luvun väliltä 0-max
     * @pre -
     * @param max suurin sallittu luku
     * @return satunnainen luku
     * @post Poikkeustakuu: vahva
     */
	unsigned int uint(unsigned int max);

    /**
     * @brief die tuottaa nopanheiton tuloksen, eli satunnaisen luvun 1-6
     * @pre -
     * @return satunnainen luku
     * @post Poikkeustakuu: vahva
     */
	unsigned short die();

private:
	Random();

	Random(const Random&) = delete;
	Random& operator =(const Random&) = delete;

    std::default_random_engine generator_;
};

} // Interface

#endif // RANDOM_H
