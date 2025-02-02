# sbf-painel

Código para um painel de controle de fontes para a SBF, Associação Brasileira de Ferromodelismo.

<img src="sbf-painel-frente.jpg" width="400"/>

## Diagrama de estados do painel

<img src="panel-states.png" width="400"/>

Nota: Além dos controles visíveis,
o painel tem um jumper interno de manutenção que precisa estar conectado a GND para habilitar o painel.
Quando este jumper é desconectado, todos os leds e relés são desligados
e os botões não têm efeito.

### Estados

#### `standby`

* `external_led`, `digital_led`, `analog_led`, piscando;
* `track_led` e `wifi_led` desligados;
* todos os relés desligados;
* transição para `wifi_selected` após segurar o `analog_button` por 5s SE
  o `direction_button` estiver apertado no momento da transição (ao final dos 5s);
* transição para `external_selected`, `digital_selected`, ou `analog_selected` após segurar o botão correspondente por 5s;

#### `external_selected`

* `external_led` ligado, todos os demais desligados;
* `external_relay` ligado, todos os demais desligados;
* transições:
  * para `standby` ao pressionar `external_button`;
  * para `track_active` ao pressionar `track`;

#### `digital_selected`

* `digital_led` ligado, todos os demais desligados;
* `digital_relay` ligado, todos os demais desligados;
* transições:
  * para `standby` ao pressionar `digital_button`;
  * para `track_active` ao pressionar `track_button`;

#### `analog_selected`

* `analog_led` ligado, todos os demais desligados;
* `analog_relay` ligado, todos os demais desligados;
* transições:
  * para `standby` ao pressionar `analog_button`;
  * para `track_active` ao pressionar `track_button`;

#### `wifi_selected`

* `wifi_led` e `analog_led` ligados, todos os demais desligados;
* `wifi_relay` ligado, todos os demais desligados;
* transições:
  * para `standby` ao pressionar `analog_button`;
  * para `track_active` ao pressionar `track_button`;

#### `track_active`

* `track_led` ligado;
* led e relé da fonte selecionada ligados (dois leds no caso de `wifi_selected`), demais desligados;
* transições:
  * **parada de emergência**: transição para modo `*_selected` anterior ao pressioar `track_button`;
  * **curto circuito**: transição para `track_protected` se o pino `short_detected` mudar para LOW (?);

#### `track_protected`

* `track_led` piscando;
* led da fonte selecionada ligado (dois leds no caso de `wifi_selected`), demais desligados;
* todos os relés desligados;
* transição para modo `*_selected` anterior se o pino `short_detected` mudar para HIGH (?);
