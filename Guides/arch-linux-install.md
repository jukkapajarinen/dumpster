# Arch Linux Base Installation :mage:
 
My usual setup for Arch Linux. Assuming EFI system, `/dev/sda` and timezone in Finland. 
Locale en_IE is for Ireland, great for Non-UK Europeans using English. 
Credits to Arch Linux Wiki and Distrotube!
 
## Setup for live env
```
loadkeys fi;
timedatectl set-ntp true;
iwctl; #this is a pre-installed wifi-tool. (skip to next section, if ethernet)
#[iwd] device list; 
#[iwd] station <wlan0> scan; 
#[iwd] station <wlan0> get-networks;
#[iwd] station <wlan0> connect <SSID>;
```
 
## Partition and format disk(s)
```
fdisk -l;
fdisk /dev/sda; #use m for help, and do +550M EFI & MAX-550M Linux
mkfs.fat -F32 /dev/sda1;
mkfs.ext4 /dev/sda2;
```
 
## Install Arch base system
```
mount /dev/sda2 /mnt;
pacstrap /mnt base linux linux-firmware;
genfstab -U /mnt >> /mnt/etc/fstab;
arch-chroot /mnt;
```
 
## Setup system files
```
ln -sf /usr/share/zoneinfo/Europe/Helsinki /etc/localtime;
hwclock --systohc;
pacman -S neovim;
nvim /etc/locale.gen; #(en_IE.UTF-8 & fi_FI.UTF-8)
locale-gen;
nvim /etc/locale.conf; #(LANG=en_IE.UTF-8)
nvim /etc/vconsole.conf; #(KEYMAP=fi)
nvim /etc/hostname; #(arkki)
nvim /etc/hosts; #(see arch wiki)
```
 
## Create user(s)
```
passwd;
useradd -m jukkapajarinen;
passwd jukkapajarinen;
usermod -aG wheel,audio,video,optical,storage jukkapajarinen;
pacman -S sudo;
EDITOR=nvim visudo; #(%wheel ALL=(ALL) ALL)
```
 
## Install EFI bootloader
```
pacman -S grub efibootmgr dosfstools os-prober mtools;
mount /dev/sda1 /mnt;
grub-install --target=x86_64-efi --bootloader-id=grub_uefi --efi-directory=/mnt --recheck --removable;
grub-mkconfig -o /boot/grub/grub.cfg;
```
 
## Ensure networking
```
pacman -S networkmanager;
systemctl enable NetworkManager;
```
 
Reboot, and that's it. If you had wifi, use `nmcli` to connect to your wifi.  
Now you'll be ready to turn it into something shiny! :sparkles: