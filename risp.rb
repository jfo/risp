require "pry"

# I am ruby derrr
class Array
    def val
        return "djiofdjsiofsj"
    end
end
# I am ruby derrrrrrrrrrrrp

class Thingy
    attr_accessor :val

    def initialize(val)
        @val = val
    end
end

class Literal < Thingy
end

class Identifier < Thingy
end


class Context
    attr_accessor :scope, :parent

    def initialize(scope, parent = nil)
        @scope = scope
        @parent = parent
    end

    def get(identifier)
        if @scope.public_methods(false).include? identifier
            @scope[identifier]
        elsif @parent != nil
            @parent.get identifier
        end
    end
end

def tokenize(string)
    string
        .gsub(/\(/, " ( " )
        .gsub(/\)/, " ) ")
        .split(/\s+/)[1..-1]
end

def parenthesize(input, list = [])
    token = input.shift
    if token == nil
        list.pop
    elsif token == "("
        list.push(parenthesize(input, []))
        parenthesize(input, list)
    elsif token == ")"
        list
    else
        parenthesize(input, list.push(categorize(token)))
    end
end

def categorize(token)
    if token.match(/[0-9]/) && !token.match(/[a-zA-Z]/)
        Literal.new(token.to_i)
    elsif token[0] == "\"" && token[-1] == "\""
        Literal.new(token[1..-2])
    else
        Identifier.new(token)
    end
end

def parse(input)
    parenthesize(tokenize(input))
end

class Library
    def first
    end
    def rest
    end
    def print
    end
end

@special = {
    "lambda" => Proc.new do |input, context|
        out = Proc.new do |*arguments|
            lambda_arguments = arguments
            lambda_scope = input[1].reduce do |acc,x,i|
                acc[x.val] = lambda_arguments[i]
                acc
            end
            interpret(input[2], Context.new(lambda_scope, context))
        end
    end
}

def interpret(input, context = nil)
    if context == nil
        interpret(input, Context.new(Library.new))
    elsif (input.class == Array)
        interpret_list(input, context)
    elsif input.class == Identifier
        context.get(input.val)
    else
        input.val
    end
end

def interpret_list(input, context)
    if !input.empty? && input.first.class != Array && @special.include?(input.first.val)
        @special[input.first.val].call(input, context)
    else
        list = input.each {|x|  interpret x, context}
        if list.first.val.class == Proc
            list.first.call(list.rest, context)
        else
            list
        end
    end
end

file = File.open("./test.ri", "r").readlines.join
input = parse(file)

p interpret(input)
