@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.route') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.route') }}
@endsection

@section('content')
    @include('routes.route_table')
@endsection
