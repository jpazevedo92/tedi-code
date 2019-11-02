@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.route_insert') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.route_insert') }}
@endsection

@section('content')
	@include('forms.route_form')
@endsection
