# Generated by Django 3.1.3 on 2020-12-16 06:56

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='User',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=30)),
                ('username', models.CharField(max_length=30, unique=True)),
                ('password', models.CharField(max_length=20)),
                ('status', models.BooleanField(default=False)),
                ('created_at', models.DateTimeField(auto_now_add=True)),
                ('is_admin', models.BooleanField(default=False)),
            ],
        ),
        migrations.CreateModel(
            name='Room',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('room_status', models.CharField(choices=[('OPEN', 'OPEN'), ('PRIVATE', 'PRIVATE')], default='OPEN', max_length=20)),
                ('name', models.CharField(default=None, max_length=20, null=True)),
                ('admin_room', models.IntegerField()),
                ('member', models.ManyToManyField(to='chat_app_service.User')),
            ],
        ),
        migrations.CreateModel(
            name='Message',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('from_user', models.IntegerField()),
                ('message', models.TextField()),
                ('created_at', models.DateTimeField(auto_now_add=True)),
                ('member', models.ManyToManyField(to='chat_app_service.User')),
                ('room', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='chat_app_service.room')),
            ],
        ),
        migrations.CreateModel(
            name='Friends',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('friend', models.IntegerField(null=True)),
                ('confirm', models.BooleanField(default=False)),
                ('user', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='chat_app_service.user')),
            ],
        ),
    ]
