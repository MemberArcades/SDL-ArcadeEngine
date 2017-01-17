#pragma once

/* Запускает контроль частоты кадров. */
void fps_init(int frequency);

/* Устанавливает заданную частоту каждров. */
void fps_set_frequency(int frequency);

/* Поддерживает частоту заданную частоту кадров. */
void fps_sleep(void);
