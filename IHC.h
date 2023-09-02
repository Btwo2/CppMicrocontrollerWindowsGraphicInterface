#ifndef IHC_H
#define IHC_H

using namespace std;

/**
 * Classe de apoio para interface com usuario.
 *
 * Para usar os metodos deve-se fazer, por exemplo, IHC::sleep().
 *
 * @Version EP2
 */
class IHC {
public:
  /**
   * Informa se a tecla ESC foi pressionada.
   */
  static bool escFoiPressionado();

  /**
   * Espera por alguns ms.
   */
  static void sleep();
private:
    /**
     * Impede a criacao de objetos deste tipo.
     */
    IHC();
};

#endif // IHC_H
