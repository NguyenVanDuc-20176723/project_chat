# Generated by Django 3.1.3 on 2021-01-02 15:52

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('chat_app_service', '0002_auto_20201216_0659'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='message',
            name='member',
        ),
    ]
