# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  config.vm.box = "debian/contrib-stretch64"

  # Forward mdbook port
  config.vm.network "forwarded_port", guest: 3000, host: 3000

  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get install -y -q \
      curl \
      golang \
      make \
      openssl \
      python3
    curl https://sh.rustup.rs -sSf | sudo -u vagrant sh -s -- -y
    if [ ! -e /home/vagrant/.cargo/bin/mdbook ]
    then
      sudo -u vagrant /home/vagrant/.cargo/bin/cargo install mdbook
    fi
  SHELL
end
