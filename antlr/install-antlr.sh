#!/usr/bin/env bash
# Install Java + ANTLR 4.13.2 tool + C++ runtime into /usr/local.
# Run with sudo:  sudo bash install-antlr.sh
set -euo pipefail

echo "==> Installing Java runtime (openjdk-17-jre-headless) ..."
apt-get update -y
apt-get install -y openjdk-17-jre-headless

echo "==> Verifying java ..."
java -version

echo "==> Installing ANTLR 4.13.2 tool jar ..."
ANTLR_JAR=/usr/local/lib/antlr-4.13.2-complete.jar
wget -q -O "$ANTLR_JAR" \
  https://www.antlr.org/download/antlr-4.13.2-complete.jar

cat > /usr/local/bin/antlr4 <<'EOF'
#!/usr/bin/env bash
java -Xmx512M -cp /usr/local/lib/antlr-4.13.2-complete.jar org.antlr.v4.Tool "$@"
EOF
chmod +x /usr/local/bin/antlr4

echo "==> Installing ANTLR4 C++ runtime from source ..."
rm -rf /tmp/antlr4-runtime-src
git clone --depth 1 \
  https://github.com/Irtiaz/antlr4.git /tmp/antlr4-runtime-src
cd /tmp/antlr4-runtime-src/runtime/Cpp
rm -rf build && mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
      -DANTLR4_WITH_TESTING=OFF \
      -DANTLR4_BUILD_CPP_TESTS=OFF \
      ..
make -j"$(nproc)"
make install

ldconfig

echo "==> Done. Verifying ..."
antlr4
echo "--- headers ---"
ls /usr/local/include/antlr4-runtime | head
echo "--- libs ---"
ls /usr/local/lib/libantlr4-runtime*
