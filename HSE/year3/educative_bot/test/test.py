import telegram
from telegram.ext import Updater
updater = Updater(token='1529712763:AAF-v-gV_ul1oyTOcfu4HsVjKhDfoulmY-s', use_context=True)
import logging
logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
                     level=logging.INFO)


def start(update, context):
    context.bot.send_message(chat_id=update.effective_chat.id, text="I'm a bot, please talk to me!")

start(updater, 'hi')