#motion_server.rb

require 'sinatra'
require 'sinatra/reloader'
require 'pry'

get '/' do
  'Hello World'
end

get '/reserved/:room' do
  room = params[:room]
  reserved = true
  puts "IS #{room} RESERVED? => #{reserved}"
  rtn = reserved ? "1" : "0"
  rtn
end

get '/display/:room' do
  room = params[:room]
#--------1---------2---------3---------4
rtn = <<-RESPONSE
DATA
NOW: #{Time.now.strftime("%^a %l:%M:%S %p")}
12345678901234567890
NEXT:       #{Time.now.strftime("%l:%M %p")}
Ben's & Antall's su
RESPONSE
rtn.strip
end

post '/occupied/:room' do
  occupied = ( request.body.read&.to_i == 1)
  str = occupied ? "OCCUPIED" : "EMPTY"
  puts str
  str
end
