import smtplib
import sys
import os
from email.utils import parseaddr
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText


# ==========================================
# CONFIGURAÇÕES
# ==========================================

EMAIL_REMETENTE = os.environ.get("UAIBANK_EMAIL_REMETENTE", "")
SENHA_APP = os.environ.get("UAIBANK_SENHA_APP", "")


# ==========================================
# FUNÇÃO PARA ENVIAR O E-MAIL
# ==========================================

def enviar_email_2FA(codigo, email_destino):

    if not EMAIL_REMETENTE or not SENHA_APP:
        print("E-mail não configurado. Defina UAIBANK_EMAIL_REMETENTE e UAIBANK_SENHA_APP.")
        return 1

    # Esta checagem rejeita endereços malformados antes de tentar o SMTP.
    # Ela não consegue confirmar se uma caixa postal realmente existe.
    _, endereco = parseaddr(email_destino)
    if endereco != email_destino or "@" not in endereco or "." not in endereco.rsplit("@", 1)[1]:
        print("E-mail inválido ou não encontrado: informe um endereço válido.")
        return 1

    print("Iniciando envio do e-mail...")

    mensagem = MIMEMultipart("alternative")

    mensagem["Subject"] = "🔐 Código de recuperação — UAIBANK"
    mensagem["From"] = EMAIL_REMETENTE
    mensagem["To"] = email_destino

    # ------------------------------------------
    # E-MAIL EM HTML
    # ------------------------------------------

    html = f"""
    <!DOCTYPE html>

    <html>

    <head>

        <meta charset="UTF-8">

        <style>

            body {{
                margin: 0;
                padding: 0;
                background-color: #f4f6f8;
                font-family: Arial, Helvetica, sans-serif;
            }}

            .container {{
                max-width: 600px;
                margin: 40px auto;
                background-color: white;
                border-radius: 12px;
                overflow: hidden;
                box-shadow: 0 4px 15px rgba(0,0,0,0.08);
            }}

            .header {{
                background-color: #111827;
                color: white;
                text-align: center;
                padding: 28px;
            }}

            .logo {{
                font-size: 28px;
                font-weight: bold;
                letter-spacing: 1px;
            }}

            .subtitle {{
                margin-top: 8px;
                font-size: 14px;
                color: #d1d5db;
            }}

            .content {{
                padding: 35px;
                color: #374151;
            }}

            .content h2 {{
                color: #111827;
            }}

            .code {{
                background-color: #f3f4f6;
                border: 2px dashed #9ca3af;
                border-radius: 10px;
                text-align: center;
                padding: 20px;
                margin: 25px 0;

                font-size: 36px;
                font-weight: bold;
                letter-spacing: 8px;

                color: #111827;
            }}

            .warning {{
                background-color: #fff7ed;
                border-left: 4px solid #f97316;

                padding: 15px;
                margin-top: 25px;

                font-size: 14px;
                color: #7c2d12;
            }}

            .footer {{
                background-color: #f9fafb;

                text-align: center;

                padding: 20px;

                color: #9ca3af;

                font-size: 12px;
            }}

        </style>

    </head>


    <body>

        <div class="container">


            <!-- CABEÇALHO -->

            <div class="header">

                <div class="logo">
                    UAIBANK
                </div>

                <div class="subtitle">
                    Segurança da sua conta
                </div>

            </div>


            <!-- CONTEÚDO -->

            <div class="content">

                <h2>Olá!</h2>

                <p>
                    Recebemos uma solicitação para recuperar
                    a senha da sua conta no <strong>UAIBANK</strong>.
                </p>

                <p>
                    Para continuar, utilize o código de verificação abaixo:
                </p>


                <!-- CÓDIGO -->

                <div class="code">

                    {codigo}

                </div>


                <p>
                    Digite este código no aplicativo para confirmar
                    sua identidade e criar uma nova senha.
                </p>


                <!-- AVISO -->

                <div class="warning">

                    <strong>⚠️ Atenção:</strong>

                    <br><br>

                    Nunca compartilhe este código com outras pessoas.

                    O UAIBANK nunca solicitará seu código por telefone,
                    mensagem ou outro meio.

                </div>

            </div>


            <!-- RODAPÉ -->

            <div class="footer">

                Este é um e-mail automático.
                Por favor, não responda a esta mensagem.

                <br><br>

                © 2026 UAIBANK

            </div>


        </div>

    </body>

    </html>
    """


    # ------------------------------------------
    # ADICIONA O HTML AO E-MAIL
    # ------------------------------------------

    mensagem.attach(
        MIMEText(html, "html", "utf-8")
    )


    # ------------------------------------------
    # CONEXÃO COM GMAIL
    # ------------------------------------------

    try:

        print("Conectando ao Gmail...")

        with smtplib.SMTP("smtp.gmail.com", 587) as servidor:

            servidor.ehlo()

            servidor.starttls()

            servidor.ehlo()

            print("Autenticando...")

            servidor.login(
                EMAIL_REMETENTE,
                SENHA_APP
            )

            print("Enviando mensagem...")

            servidor.send_message(mensagem)


        print("E-mail enviado com sucesso!")
        return 0


    except Exception as erro:

        print("Erro ao enviar e-mail:")

        print(erro)
        return 1



# ==========================================
# EXECUÇÃO PELO C
# ==========================================

if __name__ == "__main__":

    # Verifica se o C passou os argumentos corretamente

    if len(sys.argv) != 3:

        print("Uso correto:")

        print(
            "python enviar_email.py CODIGO EMAIL"
        )

        sys.exit(1)


    # Primeiro argumento = código

    codigo = sys.argv[1]


    # Segundo argumento = e-mail

    email_destino = sys.argv[2]


    # Executa o envio

    sys.exit(enviar_email_2FA(
        codigo,
        email_destino
    ))
