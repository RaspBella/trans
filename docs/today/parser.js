class Token {
  constructor(type, value) {
    this.type = type;
    this.value = value;
  }
}

export class Lexer {
  constructor(input) {
    this.input = input;
    this.pos = 0;
    this.c = input[0];
  }

  error() {
    throw new Error("Invalid character");
  }

  advance() {
    this.pos++;

    if (this.pos > this.input.length - 1) {
      this.c = null;
    } else {
      this.c = this.input[this.pos];
    }
  }

  is_whitespace(char) {
    return " \v\t\r\n".indexOf(char) != -1;
  }

  is_digit(char) {
    return char >= "0" && char <= "9";
  }

  is_op(char) {
    return char == "+" || char == "-";
  }

  is_unit(char) {
    return "yYmMwWdD".indexOf(char) != -1;
  }

  skip_whitespace() {
    while (this.c != null && this.is_whitespace(this.c)) {
      this.advance();
    }
  }

  num() {
    let result = "";

    while (this.c != null && this.is_digit(this.c)) {
      result += this.c;

      this.advance();
    }

    return parseInt(result);
  }

  lex() {
    while (this.c != null) {
      if (this.is_whitespace(this.c)) {
        this.skip_whitespace();

        continue;
      }

      if (this.is_digit(this.c)) {
        return new Token("NUM", this.num());
      }

      if (this.is_op(this.c)) {
        let token = new Token("OP", this.c);

        this.advance();

        return token;
      }

      if (this.is_unit(this.c)) {
        let token = new Token("UNIT", this.c.toLowerCase());

        this.advance();

        return token;
      }

      this.error();
    }

    return new Token("EOF", null);
  }
}

export class Parser {
  constructor(lexer, date) {
    this.lexer = lexer;
    this.date = date;
    this.token = lexer.lex();
  }

  error() {
    throw new Error("Invalid syntax");
  }

  eat(type) {
    if (this.token.type == type) {
      this.token = this.lexer.lex();
    }
    else {
      this.error();
    }
  }

  up_date() {
    let op = this.token;

    this.eat("OP");

    let num = this.token;

    this.eat("NUM");

    let unit = this.token;

    this.eat("UNIT");

    switch (op.value) {
      case "+":
        op = (get, set, num) => set(get() + num);
        break;

      case "-":
        op = (get, set, num) => set(get() - num);
        break;

      default:
        throw new Error("unreachable");
    }

    switch (unit.value) {
      case "y":
        op(() => this.date.getFullYear(), (num) => this.date.setFullYear(num), num.value);
        break;

      case "m":
        op(() => this.date.getMonth() + 1, (num) => this.date.setMonth(num - 1), num.value);
        break;

      case "w":
        op(() => this.date.getDate(), (num) => this.date.setDate(num), 7 * num.value);
        break;

      case "d":
        op(() => this.date.getDate(), (num) => this.date.setDate(num), num.value);
        break;

      default:
        throw new Error("unreachable");
    }
  }

  parse() {
    while (this.token.type == "OP") {
      this.up_date();
    }

    return this.date;
  }
}
