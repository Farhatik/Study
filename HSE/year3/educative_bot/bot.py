import prettytable as pt
import telebot
import config
from telebot import types
import numpy as np
import pandas as pd
from tabulate import tabulate

list_topics = '1. Предел последовательности\n'\
        '2. Предел функции\n'\
        '3. Прозводная\n'\
        '4. Правило Лопиталя\n'\
        '5. Формула Тейлора\n'\
        '6. Вычисление пределов с помощью формулы Тейлора\n'\
        '7. Общие приемы и методы интегрирования\n'\
        '8. Интегрирование рациональных функций\n'\
        '9. Интегрирование иррациональных функций\n'\
        '10. Определенный интеграл\n'\
        '11. Несобственные интегралы от неограниченных функций\n'\
        '12. Ряды с неотрицательными членами\n'\
        '13. Абсолютно и не абсолютно сходящиеся ряды\n'\
        '14. Степенные ряды\n'\
        '15. Тригонометрические ряды Фурье\n'\
        '\n'\
        '<b>Введите номер темы:</b>'

NUM_TOPICS = 15
NUM_tasks = [9, 5, 8, 7, 7,
             9, 9, 7, 7, 10,
             10, 9, 5, 5, 6]

bot = telebot.TeleBot(config.TOKEN)

base_markup = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
base_item1 = types.KeyboardButton('/topics')
base_item2 = types.KeyboardButton('/stat')
base_item3 = types.KeyboardButton('/help')
base_markup.add(base_item1, base_item2, base_item3)


@bot.message_handler(commands=['start'])
def welcome(message):
    markup = types.ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    item1 = types.KeyboardButton('Список тем')
    markup.add(item1)
    bot.send_message(message.chat.id,
                     "Добро пожаловать, {0.first_name}!"
                     "\nЯ - <b>{1.first_name}</b>, " 
                     "созданный чтобы помогать студентам готовиться к математическому анализу.\n"
                     "Чтобы начать работу, нужно выбрать тему из предложенного списка".format(
                         message.from_user, bot.get_me()), parse_mode='html', reply_markup=markup)


@bot.message_handler(commands=['help'])
def help(message):
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    item1 = types.KeyboardButton('/topics')
    item2 = types.KeyboardButton('/stat')
    markup.add(item1, item2)
    bot.send_message(message.chat.id, 'Как пользоваться чат-ботом?\n\n'
                                      '1) Посмотреть список доступных тем можно с помощью команды /topics внизу экрана, либо написав сообщение "Список тем". Выберите тему, которую вы хотите изучить;\n\n'
                                      '2) Выберите номер задачи, которую вы хотите решить;\n\n'
                                      '3) После прорешивания задачи, сравните с правильным вариантом ответа, который вам пришлет бот;\n\n'
                                      '4) Бот отслеживет ваш прогресс, чтобы просмотреть статистику решенных задач, воспользуйтесь командой /stat;\n\n'
                                      '5) Бонусная функция – "Посмотреть полезные материалы по теме". Воспользуйтесь данной командой при необходимости изучить теоретические материалы по конкретной теме дополнительно.\n\n'
                                      'Желаем успехов в изучении высшей математики!'
                     , reply_markup=markup)


@bot.message_handler(commands=['topics'])
def topics(message):
    msg = bot.send_message(message.chat.id, list_topics, parse_mode='html', reply_markup=base_markup)
    bot.register_next_step_handler(msg, choose_topic)


@bot.message_handler(commands=['stat'])
def stat(message):
    #  'user', 'task_topic', 'task_num', 'is_right'
    table = pd.read_csv('stat.csv')
    table = table[table.user == message.from_user.id]
    t = table[['task_topic', 'task_num', 'is_right']].to_markdown(tablefmt='simple',
                                                                  index=False,
                                                                  headers=['Тема', 'Задание', 'Верно?'])
    bot.send_message(message.chat.id, f'<pre>{t}</pre>', parse_mode='html', reply_markup=base_markup)


@bot.message_handler(content_types=['text'])
def show_list_topics(message):
    if message.text.lower() == 'список тем' or message.text.lower() == '/topics':
        msg = bot.send_message(message.chat.id, list_topics, parse_mode='html', reply_markup=base_markup)
        bot.register_next_step_handler(msg, choose_topic)


@bot.message_handler(content_types=['text'])
def choose_topic(message):
    topics_ar = (np.arange(NUM_TOPICS) + 1).astype('str')
    msg = None
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    item1 = types.KeyboardButton('Показать справочные материалы по данной теме')
    item2 = types.KeyboardButton('/topics')
    item3 = types.KeyboardButton('/stat')
    item4 = types.KeyboardButton('/help')
    markup.add(item4, item2, item3, item1)
    if message.text == 'help' or message.text == '/help':
        help(message)
    elif message.text == 'topics' or message.text == '/topics':
        topics(message)
    elif message.text == 'stat' or message.text == '/stat':
        stat(message)
    elif message.text not in topics_ar:
        msg = bot.send_message(message.chat.id, 'Неправильно введен номер темы. Попробуйте еще раз.')
        bot.register_next_step_handler(message, choose_topic)
    elif message.text.lower() == '1' or message.text.lower() == 'предел последовательности':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Предел последовательности":\n'
                                                "1. Доказать исходя из определения, что некоторое число является пределом последовательности (легкая версия)\n"
                                                "2. Доказать исходя из определения, что некоторое число является пределом последовательности (чуть сложнее)\n"
                                                "3. Доказать, что последовательность расходится (легкая версия)\n"
                                                "4. Доказать, что последовательность расходится (чуть сложнее)\n"
                                                "4. Доказать, что последовательность неограниченна\n"
                                                "5. Найти предел последовательности (легкая версия)\n"
                                                "6. Доказать, что предел последовательности равен числу\n"
                                                "7. Доказать, что предел последовательности равен нулю с параметром\n"
                                                "8. Найти предел последовательности (средний уровень)\n"
                                                "9. Найти предел последовательности (сложный уровень)\n"
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '2' or message.text.lower() == 'предел функции\n':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Предел последовательности":\n'
                                          '1. Доказать, используя определение Коши предела функции\n'
                                          '2. Доказать, что функция не имеет предела в точке\n'
                                          '3. Найти пределы четырех функций (легкий уровень)\n'
                                          '4. Найти пределы четырех функций (средний уровень)\n'
                                          '5. Найти пределы четырех функций (сложный уровень)\n'
                                          "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '3' or message.text.lower() == 'производная':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Прозводная":\n'
                                          '1. Найти производную функции (легкий уровень)\n'
                                          '2. Вычислить производную функции в точке\n'
                                          '3. Вычислить производную функции (средний уровень)\n'
                                          '4. Найти производные двух функций с помощью правило дифференцирования сложной функции\n'
                                          '5.  Вычислить производную функции (средний уровень+)\n'
                                          '6.  Вычислить производную функции (средний уровень++)\n'
                                          '7.  Доказать равенство\n'
                                          '8.  Вычислить производную функции (сложный уровень)\n'
                                          "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '4' or message.text.lower() == 'правило лопиталя':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Правило Лопиталя":\n'
                                          '1. Найти предел функции (легкий уровень)\n'
                                          '2. Найти предел функции (легкий уровень+)\n'
                                          '3. Найти предел функции (средний уровень)\n'
                                          '4. Найти придел функции (средний уровень+)\n'
                                          '5. Найти предел функции (средний уровень++)\n'
                                          '6. Найти предел функции (сложный уровень)\n'
                                          '7. Найти предел (с параметрами)\n'
                                          "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '5' or message.text.lower() == 'формула тейлора':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "формула Тейлора":\n'
                                                '1. Представить формулой Маклорена\n'
                                                '2. Представить формулой Маклорена (легкий уровень+)\n'
                                                '3. Представить формулой Маклорена (средний уровень)\n'
                                                '4. Представить формулой Маклорена (средний уровень+)\n'
                                                '5. Представить формулой Маклорена (средний уровень++)\n'
                                                '6. Представить формулой Маклорена (сложный уровень)\n'
                                                '7. Представить формулой Маклорена (сложный уровень+)\n'
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '6':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Вычисление пределов с помощью формулы Тейлора":\n'
                                                '1. Найти предел функции (легкий уровень)\n'
                                                '2. Найти предел функции (легкий уровень+)\n'
                                                '3. Найти предел функции (легкий уровень++)\n'
                                                '4. Найти предел функции (средний уровень)\n'
                                                '5. Найти придел функции (средний уровень+)\n'
                                                '6. Найти предел функции (средний уровень++)\n'
                                                '7. Найти предел функции (сложный уровень)\n'
                                                '8. Найти предел функции (сложный уровень+)\n'
                                                '9. Найти предел функции (сложный уровень++)\n'
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '7' or message.text.lower() == 'общие приемы и методы интегрирования':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Вычисление пределов с помощью формулы Тейлора":\n'
                                                '1. Найти первообразную функции (легкий уровень)\n'
                                                '2. Найти первообразную функции (легкий уровень+)\n'
                                                '3. Найти интеграл (легкий уровень++)\n'
                                                '4. Найти интеграл (средний уровень)\n'
                                                '5. Найти интеграл (средний уровень+)\n'
                                                '6. Найти интеграл (средний уровень++)\n'
                                                '7. Найти интеграл (сложный уровень)\n'
                                                '8. Найти интеграл (сложный уровень+)\n'
                                                '9. Найти интеграл (сложный уровень++)\n'
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '8' or message.text.lower() == 'интегрирование рациональных функций':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Интегрирование рациональных функций":\n'
                                                '1. Найти интеграл (легкий уровень)\n'
                                                '2. Найти интеграл (легкий уровень+)\n'
                                                '3. Найти интеграл (средний уровень)\n'
                                                '4. Найти интеграл (средний уровень+)\n'
                                                '5. Найти интеграл (сложный уровень)\n'
                                                '6. Найти интеграл (сложный уровень+)\n'
                                                '7. Найти интеграл (сложный уровень++)\n'
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '9' or message.text.lower() == 'интегрирование иррациональных функций':
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Интегрирование иррациональных функций":\n'
                                                '1. Найти интеграл (легкий уровень)\n'
                                                '2. Найти интеграл (легкий уровень+)\n'
                                                '3. Найти интеграл (средний уровень)\n'
                                                '4. Найти интеграл (средний уровень+)\n'
                                                '5. Найти интеграл (сложный уровень)\n'
                                                '6. Найти интеграл (сложный уровень+)\n'
                                                '7. Найти интеграл (сложный уровень++)\n'
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '10' or message.text.lower():
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Интегрирование иррациональных функций":\n'
                                                '1. Доказать, что всякая непрерывная на отрезке функция интегрируема на нем.\n'
                                                '2. Найти интеграл с помощью интегральных сумм\n'
                                                '3. Доказать, что для того чтобы фцнкция была интгрируема на отрезке, необходимо и достаточно, чтобы выполнялось некое условие\n'
                                                '4. Доказать свойство\n'
                                                '5. Найти интеграл с помощью формулы Ньютона-Лейбница\n'
                                                '6. Найти интеграл (легкий уровень)\n'
                                                '7. Найти интеграл (средний уровень)\n'
                                                '8. Найти интеграл (сложный уровень)\n'
                                                '9. Доказать равенство\n'
                                                '10. Доказать неравенства\n'
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '11' or message.text.lower():
        msg = bot.send_message(message.chat.id, 'Список задач по теме "Несобственные интегралы от неограниченных функций":\n'
                                                '1. Вычислить четыре интеграла (легкий уровень)\n'
                                                '2. Исследовать на сходимость (легкий уровень)\n'
                                                '3. Вычислить интеграл (средний уровень)\n'
                                                '4. Вычислить интеграл (средний уровень+)\n'
                                                '5. Вычислить интеграл (сложный уровень)\n'
                                                '6. Найти площадь фигуры, ограниченной отрезком (сложный уровень+)\n'
                                                '7. Вычислить интеграл (сложный уровень++)\n'
                                                '8. Вычислить интеграл (сложный уровень+++)\n'
                                                '9. Исследовать на сходимость (средний уровень)\n'
                                                '10. Исследовать на сходимость (сложный уровень)\n'
                                                
                                                "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '12' or message.text.lower(): #Ряды с неотрицательными членами
        msg = bot.send_message(message.chat.id,
                               'Список задач по теме "Ряды с неотрицательными членами":\n'
                               '1. Исследовать на сходимость (легкий уровень)\n'
                               '2. Исследовать на сходимость (легкий уровень+)\n'
                               '3. Исследовать на сходимость (легкий уровень)\n'
                               '4. Исследовать на сходимость (средний уровень+)\n'
                               '5. Исследовать на сходимость (средний уровень)\n'
                               '6. Исследовать на сходимость с помощью признака Даламбера\n'
                               '7. Исследовать на сходимость с помощью признака Коши\n'
                               '8. Исследовать на сходимость с помощью признака Раабе\n'
                               '9. Исследовать на сходимость с помощью признака Гаусса\n'

                               "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '13' or message.text.lower():
        msg = bot.send_message(message.chat.id,
                               'Список задач по теме "Абсолютно и не абсолютно сходящиеся ряды":\n'
                               '1. Доказать, что ряд абсолютно сходится \n'
                               '2. Доказать сходимость знакочередующегося ряда\n'
                               '3. Доказать сходимость ряда при условии \n'
                               '4. Исследовать на сходимость (средний уровень)\n'
                               '5. Исследовать на сходимость и абсолютную сходимость (средний уровень)\n'

                               "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '14' or message.text.lower():
        msg = bot.send_message(message.chat.id,
                               'Список задач по теме "Степенные ряды":\n'
                               '1. Найти радиус сходимости (легкий уровень)\n'
                               '2. Найти радиус сходимости (средний уровень)\n'
                               '3. Найти радиус сходимости (тяжелый уровень)\n'
                               '4. Найти сумма ряда\n'
                               '5. Доказать, что ряд равен числу \n'

                               "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)
    elif message.text.lower() == '15' or message.text.lower():
        msg = bot.send_message(message.chat.id,
                               'Список задач по теме "Тригонометрические ряды Фурье":\n'
                               '1. Найти комплексную форму ряда Фурье \n'
                               '2. Доказать, что кусочно гладкая на отрезке функция может быть разложена в данном виде\n'
                               '3. Разложить в ряд Фурье (легкий уровень)\n'
                               '4. Разложить в ряд Фурье (средний уровень)\n'
                               '5. Разложить в ряд Фурье (сложный уровень)\n'
                               '6. Доказать равенство \n'

                               "\n<b>Введите номер задачи</b>",
                               parse_mode='html', reply_markup=markup
                               )
        bot.register_next_step_handler(msg, show_tasks_topic, message.text)

@bot.message_handler(content_types=['text'])
def show_tasks_topic(message, topic):
    tasks_arr = (np.arange(NUM_tasks[int(topic) - 1]) + 1).astype('str')
    if message.text == 'Показать справочные материалы по данной теме':
        bot.send_message(message.chat.id, 'Справочные материалы')
        # sendDocument
        doc = open('topics/' + topic + '/' + topic + '.pdf', 'rb')
        bot.send_document(message.chat.id, doc, reply_markup=base_markup)
        # bot.send_document(message.chat.id, "FILEID")

    elif message.text == '/help':
        help(message)
    elif message.text == '/stat':
        stat(message)
    elif message.text == '/topics':
        topics(message)
    elif message.text not in tasks_arr:
        msg = bot.send_message(message.chat.id, 'Неправильно введен номер задачи. Попробуйте еще раз.')
        bot.register_next_step_handler(message, show_tasks_topic, topic)
    else:
        bot.send_message(message.chat.id, 'Условие задачи:')
        photo = open('topics/' + topic + '/task/' + message.text + '.png', 'rb')
        bot.send_photo(message.chat.id, photo)
        markup = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
        item = types.KeyboardButton('Показать решение задачи №' + message.text)
        markup.add(item)
        msg = bot.send_message(message.chat.id, 'Когда решите данную задачу, воспользуйтесь кнопкой снизу', reply_markup=markup)
        msg.text += message.text
        bot.register_next_step_handler(msg, show_solve_topic, topic, message.text)


@bot.message_handler(content_types=['text'])
def show_solve_topic(message, topic, task):
    bot.send_message(message.chat.id, 'Решение:')
    photo = open('topics/' + topic + '/solve/' + task + '.png', 'rb')
    bot.send_photo(message.chat.id, photo)
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    item1 = types.KeyboardButton('Да')
    item2 = types.KeyboardButton('Нет')
    item3 = types.KeyboardButton('+/-')
    markup.add(item1, item2, item3)
    msg = bot.send_message(message.chat.id, 'Правильно ли вы решили данную задачу?', reply_markup=markup)
    bot.register_next_step_handler(msg, molodec, topic, task)


@bot.message_handler(content_types=['text'])
def molodec(msg, topic, task):
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    item1 = types.KeyboardButton('/topics')
    item2 = types.KeyboardButton('/stat')
    item3 = types.KeyboardButton('/help')
    markup.add(item1, item2, item3)
    if msg.text == 'Да':
        bot.send_message(msg.chat.id, 'Молодец! Так держать. 🥳 ', reply_markup=markup)
    elif msg.text == 'Нет':
        bot.send_message(msg.chat.id, 'Ничего страшного. Внимательно прочитай решение и исправь ошибки', reply_markup=markup)
    elif msg.text == '+/-':
        bot.send_message(msg.chat.id, 'В следующий раз будь внимательнее и учти все моменты.', reply_markup=markup)
    df = pd.read_csv('stat.csv')
    row = pd.DataFrame([[msg.from_user.id, topic, task, msg.text]], columns=['user', 'task_topic', 'task_num', 'is_right'])
    df = df.append(row,  ignore_index=True)
    df.to_csv('stat.csv', index=False)


bot.polling(none_stop=True)
