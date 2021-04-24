from telegram import Update
from telegram.ext import Updater
from telegram.ext import CallbackContext
from telegram.ext import Filters
from telegram.ext import MessageHandler


def message_handler(udpate: Update, context: CallbackContext):
    udpate.message.reply_text(
        text='Влад соси хуй'
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



