from telegram import Update
from telegram import KeyboardButton
from telegram import ReplyKeyboardMarkup
from telegram.ext import Updater
from telegram.ext import CallbackContext
from telegram.ext import Filters
from telegram.ext import MessageHandler

button_help = 'Починить бота!'

def message_handler(udpate: Update, context: CallbackContext):
    reply_markup = ReplyKeyboardMarkup(
        keyboard=[
            [
                KeyboardButton(text=button_help),
            ],
        ],
        resize_keyboard=True,
    )

    udpate.message.reply_text(
        text='Бот в разработке',
        reply_markup=reply_markup,
    )


def main():
    updater = Updater(
        token='1529712763:AAF-v-gV_ul1oyTOcfu4HsVjKhDfoulmY-s',
        use_context=True
    )
    updater.dispatcher.add_handler(
        MessageHandler(
            filters=Filters.all,
            callback=message_handler
        )
    )

    updater.start_polling()
    updater.idle()


if __name__ == '__main__':
    main()



