class Array
    def car; self.first; end
    def cdr; self[1..-1] end
end

class String
    def tokenize; self.gsub(/\(/, " ( ").gsub(/\)/, " ) ").gsub(/\n/, " ").split(" "); end
end

def categorize(token)
    begin
        Integer(token)
    rescue
        token.to_sym
    end
end

def parenthesize(input, list = [])
    token = input.shift
    if token.nil?
        list.car
    elsif token == "("
        list << parenthesize(input)
        parenthesize input, list
    elsif token == ")"
        list
    else
        parenthesize(input, list << categorize(token))
    end
end

@standard_env = {
    :+ => ->(args){ args.inject(:+) },
    :- => ->(args){ args.inject(:-) }
}

def eval(expression, env = @standard_env)
    expression.each_with_index do |e, i|
        if e.is_a? Array
            expression[i] = eval e
        end
    end

    if expression.car == :defun
        defun(expression.cdr)
    end

    if expression.car.is_a? Symbol
        return expression.cdr.car.send(expression.car, *expression.cdr.cdr)
    end
end

@input = File.open("./test.ri", "r").read

p parenthesize(@input.tokenize)
gets
p parenthesize(@input.tokenize.push(")").unshift("(")).map {|e| eval e}.first
