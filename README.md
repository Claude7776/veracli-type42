# Veracli — Minimal Encrypted File CLI

**Veracli** est un outil en ligne de commande minimaliste écrit en **C** utilisant **OpenSSL**, inspiré par l'esprit de VeraCrypt mais dans une version extrêmement simplifiée et pédagogique (style 42 / low-level).

Il permet de chiffrer et déchiffrer des fichiers individuels avec des primitives cryptographiques modernes et sécurisées.

**Objectif principal** : apprendre et maîtriser la cryptographie appliquée en C, l'API EVP d'OpenSSL, la dérivation de clés, le padding, la gestion mémoire sécurisée et une architecture modulaire propre.

**⚠️ Important**  
Ce projet est **purement pédagogique**.  
Il n'est **pas recommandé** pour protéger des données sensibles en production (voir section Limitations).

## Fonctionnalités actuelles

- Chiffrement/déchiffrement de fichiers
- Algorithme : **AES-256-CBC**
- Dérivation de clé : **PBKDF2-HMAC-SHA256** avec 200 000 itérations
- Salt aléatoire : 16 bytes
- IV aléatoire : 16 bytes
- Padding : **PKCS#7**
- Format du fichier chiffré :


## Prérequis

- GCC ou Clang
- **OpenSSL** ≥ 1.1.1 (libcrypto + headers)
- make

### Installation des dépendances (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install libssl-dev build-essential

```

### Compilation

```bash
git clone https://github.com/VOTRE_USERNAME/veracli-type42.git
cd veracli-type42
make
```

### output après l'exécutable: ./veracli


### Utilisation
**Chiffrer un fichier**

```bash
./veracli encrypt document-confidentiel.pdf
```

**Le programme demandera deux fois le mot de passe.**
→ Crée document-confidentiel.pdf.enc

**Déchiffrer un fichier**

```bash
./veracli decrypt document-confidentiel.pdf.enc
```

Mot de passe demandé → Crée document-confidentiel.pdf.dec (ou écrase si vous forcez)
Note : le fichier chiffré garde l'extension .enc par convention.

## Structure du projet

veracli/
├── main.c          # Parsing CLI, gestion entrée/sortie utilisateur
├── crypto.c        # Toute la logique cryptographique (EVP, PBKDF2, etc.)
├── crypto.h        # Déclarations et prototypes
├── Makefile        # Compilation simple et propre
└── README.md

## Bonnes pratiques implémentées

- **Utilisation exclusive de l'API EVP (recommandée par OpenSSL)**
- **Vérifications systématiques des retours d'erreur**
- **Nettoyage mémoire sensible (OPENSSL cleanse)**
- **Gestion sécurisée des buffers**
- **Architecture modulaire (séparation CLI / crypto)**

## Limitations actuelles (très importantes)

- **Mode CBC → pas d'authentification (vulnérable aux attaques par padding oracle si mal utilisé)**
- **Pas d'AEAD (AES-GCM ou ChaCha20-Poly1305 serait préférable)**
- **Pas de HMAC pour vérifier l'intégrité**
- **Pas de protection contre la modification/suppression malveillante du fichier**
- **Pas de gestion de volumes/conteneurs comme VeraCrypt**
- **Pas de support pour les très gros fichiers (tout en RAM)**

## Améliorations prévues

- **Migration vers AES-256-GCM (AEAD)**
- **Ajout d'un HMAC-SHA256 pour l'authentification**
- **Remplacement de PBKDF2 par Argon2id (plus résistant aux attaques GPU/ASIC)**
- **Header structuré + version + paramètres**
- **Support de conteneurs / volumes chiffrés**
- **Option --output / --force / --verbose**
- **Tests unitaires (check ou cmocka)**

## Sécurité — À lire absolument ⚠️ 

Ce programme est un excellent exercice d'apprentissage, mais ne doit pas être utilisé pour des données critiques sans les améliorations listées ci-dessus.
Pour un usage réel, préférez :

- **VeraCrypt**
- **age**
- **rclone crypt**
- **gocryptfs**
- **7-Zip avec AES-256 + mot de passe fort**

## Auteur
Développé avec ❤️ dans le cadre d'un approfondissement personnel en :

- Cryptographie appliquée
- Sécurité système
- Développement bas niveau C
- Bonne architecture logicielle

N'hésite pas à ouvrir une issue ou une PR si tu veux contribuer !
