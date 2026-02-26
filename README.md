🔐 Veracli — Minimal Encrypted File CLI (C / OpenSSL)

Veracli est un outil de chiffrement en ligne de commande écrit en C, inspiré de VeraCrypt, conçu dans un esprit “low-level / type 42 school”.

Il permet de chiffrer et déchiffrer des fichiers en utilisant des primitives cryptographiques robustes fournies par OpenSSL.

🚀 Objectif du projet

Ce projet a été développé pour :

Approfondir la compréhension de la cryptographie appliquée

Manipuler l’API OpenSSL (libcrypto)

Implémenter un système de chiffrement sécurisé en C

Comprendre la dérivation de clé, le padding et la gestion mémoire

Développer une architecture propre en plusieurs fichiers (modulaire)

🔒 Caractéristiques techniques

🔐 AES-256-CBC

🧂 Salt aléatoire (16 bytes)

🔑 Dérivation de clé via PBKDF2 (SHA-256, 200 000 itérations)

🎲 IV aléatoire (16 bytes)

📦 Padding PKCS7

📁 Format du fichier chiffré :

[ SALT | IV | CIPHERTEXT ]

🛠 Implémenté avec OpenSSL (EVP API)

📂 Structure
veracli/
├── main.c
├── crypto.c
├── crypto.h
└── Makefile

Architecture modulaire :

main.c : gestion CLI

crypto.c : logique cryptographique

crypto.h : interface

Makefile : compilation

⚙️ Compilation
sudo apt install libssl-dev
make
🖥 Utilisation

Chiffrement :

./veracli encrypt fichier.txt

Déchiffrement :

./veracli decrypt fichier.txt.enc
🎓 Objectif pédagogique

Ce projet n’a pas vocation à remplacer VeraCrypt, mais à :

Comprendre les mécanismes internes du chiffrement

Manipuler AES et PBKDF2 en C

Gérer correctement la mémoire et les erreurs

Appliquer les bonnes pratiques cryptographiques modernes

⚠️ Limitations actuelles

Utilise AES-CBC (non authentifié)

Pas d’AEAD (AES-GCM recommandé pour production)

Pas de protection avancée contre modification malveillante

Pas de gestion de volumes ou conteneurs

🧠 Améliorations futures

Migration vers AES-256-GCM

Ajout d’un HMAC pour intégrité

Implémentation Argon2id

Format de header structuré

Création d’un conteneur chiffré type volume

👨‍💻 Auteur

Projet développé dans le cadre d’un approfondissement personnel en :

Cryptographie appliquée

Sécurité système

Développement bas niveau en C

Architecture sécurisée
