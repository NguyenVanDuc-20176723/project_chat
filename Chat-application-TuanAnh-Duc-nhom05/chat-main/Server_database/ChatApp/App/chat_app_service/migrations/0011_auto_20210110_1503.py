# Generated by Django 3.1.3 on 2021-01-10 15:03

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('chat_app_service', '0010_message_room'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='message',
            name='room',
        ),
        migrations.DeleteModel(
            name='ChatPrivate',
        ),
        migrations.DeleteModel(
            name='Message',
        ),
    ]
