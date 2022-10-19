% Demo of matvec with different hierarcical algorithms

function flam(n, occ, rank_or_tol, Tmax, symm) 

    % Default parameters
    if nargin < 1 || isempty(n), n = 100000; end
    if nargin < 2 || isempty(occ), occ = 200; end
    if nargin < 3 || isempty(rank_or_tol), rank_or_tol = 1e-5; end
    if nargin < 4 || isempty(Tmax), Tmax = 2; end
    if nargin < 5 || isempty(symm), symm = 'h'; end

    % Random 3D coordinates
    x = rand(3, n);
    Afun = @(i, j) Afun_(i,j,x);
    p = 64;
    proxy = trisphere_subdiv(p,'v'); r = randperm(size(proxy,2));
    proxy = proxy(:,r(1:p));  % reference proxy points are for unit box [-1, 1]^3

    pxyfun = @(x,slf,nbr,l,ctr)pxyfun_(x,slf,nbr,l,ctr,proxy);
    opts = struct('Tmax',Tmax,'symm',symm,'verb',1);
    tic; F = rskelf(Afun,x,occ,rank_or_tol,pxyfun, opts); t = toc;
    w = whos('F'); mem = w.bytes/1e6;
    fprintf('rskelf factorization time/mem: %10.4e (s) / %6.2f (MB)\n',t, mem)

    % Test matvec against random charges
    X = rand(n,1);
    tic; rskelf_mv(F, X); t = toc;
    fprintf('MatVec time: %10.4e (s)', t);
end

% proxy function
function [Kpxy, nbr] = pxyfun_(x, slf, nbr, l, ctr, proxy)
    pxy = proxy.*l + ctr;  % scale and translate reference points
    N = size(x,2);
    Kpxy = Kfun(pxy,x(:,slf))/N;
    nbr = nbr(sum(((x(:,nbr) - ctr)./l).^2) < 1.5^2);
end

% kernel function
function K = Kfun(x,y)
    dx = x(1,:)' - y(1,:);
    dy = x(2,:)' - y(2,:);
    dz = x(3,:)' - y(3,:);
    dr = sqrt(dx.^2 + dy.^2 + dz.^2);
    K = 1/(4*pi)./dr;
end
  
% matrix entries
function A = Afun_(i,j,x)
N = size(x,2);
A = Kfun(x(:,i),x(:,j));
[I,J] = ndgrid(i,j);
A(I == J) = 0;         % replace diagonal with 0
end
  

